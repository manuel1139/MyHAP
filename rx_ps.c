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

void reset_rx(remote* r) {
    r->rx_data.edge_a = 0;
    r->rx_data.bit_id = 0;
    r->rx_data.state = rx_idle;
    r->rx_data.code_received = 0;
}

void rx_ps(struct remote* r, uint16_t bit_time) {
    switch (r->rx_data.state) {
        case rx_idle: //ignore first edge
            r->rx_data.state = rx_header_a;
            break;
        case rx_header_a:
            //allow 1/16 bit time as difference
            chk_hdr_bounds(r->header.pulse, bit_time) ? r->rx_data.state = rx_header_b :
                    r->rx_data.state = rx_not_me;
            break;
        case rx_header_b:
            chk_hdr_bounds(r->header.space, bit_time) ? r->rx_data.state = rx_first_edge :
                    r->rx_data.state = rx_not_me;
            break;
        case rx_first_edge:
            r->rx_data.edge_a = bit_time;
            r->rx_data.state = rx_second_edge;
            break;
        case rx_second_edge:
            if (r->rx_data.bit_id < r->bit_cnt) {
                chk_bit_bounds(r, r->rx_data.edge_a, bit_time) ?
                        r->rx_data.state = rx_first_edge : r->rx_data.state = rx_not_me;
                if (r->rx_data.state == rx_not_me) break;

                r->rx_data.word_id = r->rx_data.bit_id / 16;

                r->rx_data.word[r->rx_data.word_id] <<= 1;

                if (r->rx_data.edge_a > bit_time) {
                    r->rx_data.word[r->rx_data.word_id] |= 1;
                }
                r->rx_data.bit_id++;
            } else {
                //rc data is big endian
                r->rx_data.word[0] = SWAP_UINT16(r->rx_data.word[0]);
                r->rx_data.word[1] = SWAP_UINT16(r->rx_data.word[1]);

                //check addres 
                if (r->dev.addr == r->rx_data.word[0]) {
                    r->rx_data.code_received = r->rx_data.word[1];
                } else {
                    r->rx_data.state = rx_not_me;
                }
                r->rx_data.state = rx_done;
            }
            break;

        case rx_not_me:
            break;
        case rx_done:
            //todo: check repeat code
            break;
        default:
            break;
    }
}
