/* 
 * File:   tx_ps.c
 * Author: manuel
 *
 * Created on 5. März 2017, 12:53
 */
#include <stdio.h>

#include "haapi.h"
#include "timer_tx.h"

#define U2T(x) x*3/2    //us to ticks @12Mhz IC

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

void tx_ps(dev_ps* y, code c) {
    const struct hw_port* d = y->hw_port;
    static uint8_t bit_cnt = 0;
    static uint8_t zero_or_one;

    switch (state) {
        case idle:
            state = header_a;
        case header_a:
            if (y->header.pulse != 0) {
                d->send();
                state = header_b;
                WriteTxTimer(0xFFFF - U2T(y->header.pulse));
                break;
            }
        case header_b:
            d->send();
            state = first_edge;
            WriteTxTimer(0xFFFF - U2T(y->header.space));
            break;
        case first_edge:
            d->send();

            //calculate next pulse space cycle for bit
            uint32_t addr_code = ((uint32_t) y->devtrgt.dev.addr << 16 | c);

            zero_or_one =
                    (addr_code >> (y->bit_cnt - bit_cnt - 1)) & 1;

            state = second_edge;

            zero_or_one ? WriteTxTimer(0xFFFF - U2T(y->one.pulse)) :
                    WriteTxTimer(0xFFFF - U2T(y->zero.pulse));
            break;
        case second_edge:
            d->send();
            bit_cnt++;
            if (bit_cnt < (y->bit_cnt)) {
                state = first_edge;
            } else {
                state = tail;
            }
            zero_or_one ? WriteTxTimer(0xFFFF - U2T(y->one.space)) :
                    WriteTxTimer(0xFFFF - U2T(y->zero.space));
            break;
        case tail:
            if (y->tail != 0) {
                d->send();
                WriteTxTimer(0xFFFF - U2T(y->tail));
            } else {
                WriteTxTimer(0xFFFF - 0x1000); //tdodo: give some time before repeat?
            }
            state = done;
            break;
        case done:
            if (y->tail != 0) {
                d->send();
            }            
            //            evdone(r);
            state = idle;
            bit_cnt = 0;
            break;
        default:
            break;
    }
}

