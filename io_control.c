#include <xc.h>
#include <stdbool.h>

#include "io_control.h"
#include "capture.h"
#include "target_dev.h"

typedef struct {
    struct target_dev* target;
    uint16_t code;
    bool isBusy;
    
} io_ctrl;

io_ctrl io_c = {0};


void send_cmd(struct target_dev *d, uint16_t code) {
    if (!io_c.isBusy) {
        io_c.isBusy = true;
        io_c.target = d;
        io_c.code = code;
        d->port->init();

        //start sending codes on the wire
        INTCONbits.TMR0IF; //hack to avoid duplicate function generation
        //r->protocol->tx(r);   //instead of this
    }
}


void StartIRReceiver() {

    CCPR1 = 0; //Timer data register zero (word)

    if (PORTCbits.RC2 == 1) {
        OpenRxCapture(CAP_EVERY_FALL_EDGE);
    } else {
        OpenRxCapture(CAP_EVERY_RISE_EDGE);
    }
    OpenRxTimer();
}


void TransmitISR() {
    if (INTCONbits.TMR0IF) {
        io_c.target->protocol->tx(io_c.target, io_c.code);
//        io_c->target->protocol->tx(io_c->target, io_c->code);

        //        if (dev.isBusy()) 
        {

            //CCP1CON = 0; //disable timer
        }

        INTCONbits.TMR0IF = 0;
    }
}