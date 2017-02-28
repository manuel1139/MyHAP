#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "system.h"
#include "target_dev.h"

bool chk_bit_bounds(const struct ps_details* r, uint16_t a, uint16_t b) {

    uint16_t diff_a, diff_b;
    bool a1, b1, a0, b0, x;

    diff_a = a >> 2;
    diff_b = b >> 2;

    a1 = (r->pulse_one < a + diff_a) && (r->pulse_one > a - diff_a); //first edge for 1
    b1 = (r->space_one < b + diff_b && r->space_one > b - diff_b); //second edge for 1
    a0 = (r->pulse_zero < a + diff_a && r->pulse_zero > a - diff_a); //first edge for 0            
    b0 = (r->space_zero < b + diff_b && r->space_zero > b - diff_b); //secode edge for 0

    x = (a1 && b1) || (a0 && b0); //todo: check for burst
    if (!x) {
        x++;
    }
    return x;
}

bool chk_hdr_bounds(uint16_t remote_time, uint16_t bit_time) {
    uint16_t diff;
    diff = remote_time >> 3; //debug only

    if (remote_time < bit_time + diff && remote_time > bit_time - diff) {
        return true;
    }
    return false;
}


enum fsm_state {
    idle,
    header_a,
    header_b,
    first_edge,
    second_edge,
    tail,
    done,
    not_me
} ;

enum fsm_state state = idle;
static uint16_t t_first_edge;
static uint16_t bit_id;
static uint32_t bits;


void reset_rx() {
    state = idle;
    t_first_edge = 0;
    bit_id = 0;
    bits = 0;
}

void rx_pulse_space(struct target_dev* r, uint16_t bit_time) {

    const struct ps_details* psd =  r->ps_data;
    
    switch (state) {
        case idle: //ignore first edge
            state = header_a;
            break;
        case header_a:
            //allow 1/16 bit time as difference
            chk_hdr_bounds(psd->hdr_time_a, bit_time) ? 
                state = header_b : state = not_me;
            break;
        case header_b:
            chk_hdr_bounds(psd->hdr_time_b, bit_time) ? state = first_edge :
                    state = not_me;
            break;          
        case first_edge:
            t_first_edge = bit_time;
            state = second_edge;
            break;
        case second_edge:
            if (bit_id < r->ps_data->bit_cnt) {
                chk_bit_bounds(r->ps_data, t_first_edge, bit_time) ?
                        state = first_edge : state = not_me;
                if (state == not_me) break;

                bits <<= 1;
                if (t_first_edge > bit_time) 
                    bits |= 1;
                
                bit_id++;
            } else {
//                ev_rx_done();
                state = done;
            }
            break;
            
        case not_me:
            break;
        case done:
            //todo: check repeat code
            break;
        default:
            break;
    }
}