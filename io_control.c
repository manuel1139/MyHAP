#include <xc.h>
#include <stdbool.h>

#include "io_control.h"
#include "capture.h"
#include "target_dev.h"
#include "pwm.h"
#include "timer_rx.h"

typedef struct {
    struct target_dev* target;
    uint16_t code;
    bool isBusy;

} io_ctrl;

io_ctrl io_c = {0};

void io_ctrl_send_cmd(struct target_dev *d, uint16_t code) {
    if (d->ps_data->port != 0) {
        if (!io_c.isBusy) {
            io_c.isBusy = true;
            io_c.target = d;
            io_c.code = code;
            //StopReceiving
            d->ps_data->port->init();

            //start sending codes on the wire
            INTCONbits.TMR0IF; //hack to avoid duplicate function generation
            //r->protocol->tx(r);   //instead of this
        }
    } else {
        //assume non exclusive device : todo :
        d->protocol->tx(d, code);
    }
}

//callback
//start_receiving//
//command dispatcher
//
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