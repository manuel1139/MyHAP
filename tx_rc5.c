#include <xc.h>

#include "tx_rc5.h"
#include "target_dev.h"
#include "timer_tx.h"

typedef enum {
    idle,
    header_a,
    header_b,
    first_edge,
    second_edge,
    tail,
    done,
    not_me
} states;

states state = idle;

typedef struct {
    uint8_t word_cnt;
    uint8_t bit_cnt;
    uint16_t edge_a_bit;
    uint16_t code_to_send;
} data;

void tx_rc5(struct target_dev* r, uint16_t code) {

    static data tx_data;
    
    const struct hw_port* d = r->port;
    
    switch (state) {
        case idle:
            state = header_a;                                
        case header_a:
            if (r->hdr_time_a != 0) {
                d->send();
                state = header_b;
                WriteTxTimer(0xFFFF - r->hdr_time_a);
                break;
            }  
        case header_b:
            d->send();
            state = first_edge;
            WriteTxTimer(0xFFFF - r->hdr_time_b);
            break;               
        case first_edge:
            d->send();
            if (tx_data.bit_cnt > 16) {
                tx_data.edge_a_bit = r->address & (1 << (tx_data.bit_cnt - 16 - 1));
            } else {
                tx_data.edge_a_bit = tx_data.code_to_send & (1 << tx_data.bit_cnt - 1);
            }
            state = second_edge;
            tx_data.edge_a_bit ? WriteTxTimer(0xFFFF - r->pulse_one) :
                    WriteTxTimer(0xFFFF - r->pulse_zero);
            break;
        case second_edge:
            d->send();
            if (tx_data.bit_cnt > 0) {
                tx_data.bit_cnt--;
                state = first_edge;
            } else {
                state = tail;
            }
            tx_data.edge_a_bit ? WriteTxTimer(0xFFFF - r->space_one) :
                    WriteTxTimer(0xFFFF - r->space_zero);
            break;
        case tail:
            WriteTxTimer(0x0F00); //trailing pulse      
            state = done;
            break;
        case done:
            break;           
        default:
            break;
    }
}


