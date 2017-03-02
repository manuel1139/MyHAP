#include "hw_port.h"
#include "pwm.h"
#include "timer_tx.h"

#include <xc.h>
#include "system.h"

void ir_send() {
    TogglePWM(); //start sending 38khz pulse
}

void ir_init() {
    OpenPWM();
    OpenTxTimer();
}

void ir_cleanup() {
    CloseTxTimer();
    ClosePWM();
}