#include <stdint.h>
#include <stdio.h>

#include "hw_ir.h"
#include "hw_rf.h"

#include "timer_tx.h"

typedef const uint16_t address;
typedef const uint16_t code;

typedef const uint16_t time_val;

typedef const uint16_t pulse;
typedef const uint16_t space;

typedef struct ps {
    pulse pulse;
    space space;
} ps;

typedef struct command {
    address addr;
    code code;
} command;

typedef struct device {
    const char *name;
    address addr;
} device;

//rc_device   dev_src
//trgt_device dev_trgt

typedef struct dev_src {
    device dev;
    void (*recv_bus)(device*, time_val);
};

void tx_ps(device*, code);
void tx_horizon(device*, code);


typedef struct dev_target {
    device dev;
    void (*send_bus)(device*, code);
} dev_target;

typedef struct dev_ps {
    dev_target dev;
    ps header;
    ps zero;
    ps one;
    uint8_t bit_cnt;
    hw_port* hw_port;
} dev_ps;

//samsung protocol
typedef struct dev_samsung {
    dev_target dev;
    ps header;
    ps zero;
    ps one;
    ps sync;
    pulse stop;
    uint8_t bit_cnt_address;
    uint8_t bit_cnt_code;
    hw_port* hw_port;
} dev_samsung;

dev_samsung horizon = {
    "Horizon Box",
    0x0,
    &tx_horizon,
    4500,
    4500,
    550,
    550,
    550,
    1650,
    550,
    4500,
    550,
    16,
    20,
    &hw_ir,
};

dev_ps yamaha = {
    "Yamaha RCV",
    0xA15E,
    &tx_ps,
    9000,   //us header
    4500,   //us
    300,
    300,
    300,
    900,
    32,
    &hw_ir,
};

int main(void) {
    yamaha.dev.send_bus((struct device*) &yamaha, 0xABCD);
}


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


void tx_ps(device* r, code c) {
    dev_ps* y = (struct dev_ps*) r;
    struct hw_port* d = y->hw_port;
    
    
    static uint8_t bit_cnt = 0;
    static uint8_t zero_or_one;

    switch (state) {
        case idle:
            state = header_a;
        case header_a:
            if (y->header.pulse != 0) {
                d->send();
                state = header_b;
                WriteTxTimer(0xFFFF - y->header.pulse);
                break;
            }
        case header_b:
            d->send();
            state = first_edge;
            WriteTxTimer(0xFFFF - y->header.space);
            break;
        case first_edge:
            d->send();
#if 0            
            //calculate next pulse space cycle for bit
            uint32_t addr_code = ((uint32_t) y->dev.address << 16 | code );

            zero_or_one = 
                    (addr_code >> (y->bit_cnt - bit_cnt - 1)) & 1;
            
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
#endif                        
        default:
            break;
    }
}


void tx_horizon(device* r, code c) {
    dev_samsung* hb = (struct dev_samsung*) r;
    struct hw_port* d = hb->hw_port;
    
    static uint8_t bit_cnt = 0;
    static uint8_t zero_or_one;

    
    
}