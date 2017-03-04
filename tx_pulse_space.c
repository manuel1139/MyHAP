#include <xc.h>
#include <stdint.h>

#include "target_dev.h"
#include "hw_port.h"
#include "timer_tx.h"
#include "dev_ps.h"
#include "system.h"
#include "t_test.h"

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

extern void evdone(struct target_dev* r);

void tx_pulse_space(const struct ps_dev* r, uint16_t code) {

    const struct hw_port* d = r->ps_data->port;
    const struct ps_details* psd =  r->ps_data;
    
    static uint8_t bit_cnt = 0;
    static uint8_t zero_or_one;

    switch (state) {
        case idle:
            state = header_a;
        case header_a:
            if (psd->hdr_time_a != 0) {
                d->send();
                state = header_b;
                WriteTxTimer(0xFFFF - psd->hdr_time_a);
                break;
            }
        case header_b:
            d->send();
            state = first_edge;
            WriteTxTimer(0xFFFF - psd->hdr_time_b);
            break;
        case first_edge:
            d->send();
            
            //calculate next pulse space cycle for bit
            uint32_t addr_code = ((uint32_t) r->address << 16 | code );

            zero_or_one = 
                    (addr_code >> (psd->bit_cnt - bit_cnt - 1)) & 1;
            
            state = second_edge;
            
            zero_or_one ? WriteTxTimer(0xFFFF - psd->space_one) :
                    WriteTxTimer(0xFFFF - psd->pulse_zero);
            break;
        case second_edge:
            d->send();         
            bit_cnt++;
            if (bit_cnt < (psd->bit_cnt)) {                
                state = first_edge;
            } else {
                state = tail;
            }
            zero_or_one ? WriteTxTimer(0xFFFF - psd->pulse_one) :
                WriteTxTimer(0xFFFF - psd->space_zero);            
            break;
        case tail:
            if (psd->tail != 0) {
                d->send();         
                WriteTxTimer(0xFFFF - psd->tail); //trailing pulse      
            } else {
                WriteTxTimer(0xFFFF - 0x1000); //
            }
            state = done;
            break;         
        case done:
            if (psd->tail != 0) {
                d->send();         
            }
    
            evdone(r);
            state = idle;
            bit_cnt=0;
            break;
        default:
            break;
    }
}


