#include <xc.h>
#include <stdbool.h>

#include "target_dev.h"

bool isBusy = false;
struct target_dev* target = 0;
uint16_t code;
typedef void (*callback)(struct target_dev*);

void send(struct target_dev* r, uint16_t c) {
    if (!isBusy) {
        isBusy = true;
        target = r;
        code = c;
        r->port->init();
        
       INTCONbits.TMR0IF;      //hack to avoid duplicate function generation
        //r->protocol->tx(r);   //instead of this
   }
}

void evdone(struct target_dev* r) {
    r->port->cleanup();
    isBusy = false;
    target = 0;
}

void TransmitISR() {
    if (INTCONbits.TMR0IF) {
        target->protocol->tx(target, code);

        //        if (dev.isBusy()) 
        {

            //CCP1CON = 0; //disable timer
        }

        INTCONbits.TMR0IF = 0;
    }
}

