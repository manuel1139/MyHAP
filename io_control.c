#include <xc.h>
#include <stdbool.h>

#include "io_control.h"
#include "capture.h"
#include "pwm.h"
#include "timer_rx.h"
#include "system.h"

#define RX_RAW

typedef struct {
    struct dev_ps* target;
    uint16_t code;
    bool isBusy;

} io_ctrl;

io_ctrl io_c = {0};

void rx_raw(uint16_t bit_time);
void rx_raw_timeo();


//stops ccp1 interrupt to disable receiving our own data
#define StopReceivingInt() PIE1bits.CCP1IE = 0; PIE1bits.TMR1IE = 0;
#define StartReceivingInt() PIE1bits.CCP1IE = 1; PIE1bits.TMR1IE  = 1;

void io_ctrl_send_cmd(dev_ps* d,  code c) {
    if (d->hw_port != 0) {
        if (!io_c.isBusy) {
            io_c.isBusy = true;
            io_c.target = d;
            io_c.code = c;

            //stop receiving to avoid receiving our own data
            StopReceivingInt();

            d->hw_port->init();

            //start sending codes on the wire
            INTCONbits.TMR0IF = 1; //hack to avoid duplicate function generation
            //r->protocol->tx(r);   //instead of this
        }
    }
}

void evdone(struct dev_ps* dt) {
    dev_ps* d = (dev_ps*) dt;
    d->hw_port->cleanup();
    io_c.isBusy = false;
    StartReceivingInt();
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
        io_c.target->tx_prot(io_c.target, io_c.code);
        INTCONbits.TMR0IF = 0;
    }
}

extern remote *remotes[];


void ReceiveISR() {
    if (PIE1bits.CCP1IE && PIR1bits.CCP1IF) {
        //inverts edge detection 
        CCP1CONbits.CCP1M0 = CCP1CONbits.CCP1M0 ^ 1;

        uint16_t cval = ReadRxCapture();

        //ticks to microseconds
        cval = T2U(cval);

#if defined RX_RAW
        rx_raw(cval); //todo:
#endif
        for (int i = 0; remotes[i]; i++) {
            remotes[i]->rx_prot(remotes[i], cval);
        }
        WriteRxTimer(0);
        PIR1bits.CCP1IF = 0;
    }

    /***************************************************************/

    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
#if defined RX_RAW
        rx_raw_timeo();
#endif
//        reset_rx();
        CCP1CON = 0;
        //reset edge detection
        IR_RCV ? CCP1CON = 0b100 : CCP1CON = 0b101;
        PIR1bits.TMR1IF = 0;

    }
}


/*
void reset_rx() {
    state = idle;
    t_first_edge = 0;
    bit_id = 0;
    bits = 0;
 }*/