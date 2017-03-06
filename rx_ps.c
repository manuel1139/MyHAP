#include <stdbool.h>

#include "haapi.h"



typedef struct {
    uint8_t word_cnt;
    uint8_t bit_cnt;
    uint16_t edge_a_bit;
    uint16_t code_to_send;
} tx_data;

typedef struct oldremote {
     char* name;
     uint16_t hdr_time_a;
     uint16_t hdr_time_b;
     uint16_t a_1;
     uint16_t b_1;
     uint16_t a_0;
     uint16_t b_0;
     uint16_t tail;
     uint16_t pre_code;
     uint8_t bit_cnt;
} oldremote;


bool chk_bit_bounds(remote* rx, uint16_t a, uint16_t b) {

    oldremote orx;
    oldremote* r = &orx;
    
    r->a_0 = rx->zero.pulse;
    r->b_0 = rx->zero.space;
    
    r->a_1 = rx->one.pulse;
    r->b_1 = rx->one.space;
            
    
    uint16_t diff_a, diff_b;
    bool a1, b1, a0, b0, x;

    diff_a = a >> 2;
    diff_b = b >> 2;

    a1 = (r->a_1 < a + diff_a) && (r->a_1 > a - diff_a); //first edge for 1
    b1 = (r->b_1 < b + diff_b && r->b_1 > b - diff_b); //second edge for 1
    a0 = (r->a_0 < a + diff_a && r->a_0 > a - diff_a); //first edge for 0            
    b0 = (r->b_0 < b + diff_b && r->b_0 > b - diff_b); //secode edge for 0

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
} state;

uint16_t rx_code_found;

void rx_ps(struct remote* r, uint16_t bit_time) {
    
    static uint16_t edge_a;
    static uint8_t bit_id;
    static uint8_t word_id;
    static uint16_t word[2];
    
    switch (state) {
        case idle: //ignore first edge
            state = header_a;
            break;
        case header_a:
            //allow 1/16 bit time as difference
            chk_hdr_bounds(r->header.pulse, bit_time) ? state = header_b :
                    state = not_me;
            break;
        case header_b:
            chk_hdr_bounds(r->header.space, bit_time) ? state = first_edge :
                    state = not_me;
            break;          
        case first_edge:
            edge_a = bit_time;
            state = second_edge;
            break;
        case second_edge:
            if (bit_id < r->bit_cnt) {
                chk_bit_bounds(r, edge_a, bit_time) ?
                        state = first_edge : state = not_me;
                if (state == not_me) break;

                word_id = bit_id / 16;

                word[word_id] <<= 1;
                //TODO:: might NOT always work!
                if (edge_a > bit_time) {

                    word[word_id] |= 1;
                }
                bit_id++;
            } else {
                //check pre-data 
                //r-> == word[0]; else not_me
                rx_code_found = word[1];
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
