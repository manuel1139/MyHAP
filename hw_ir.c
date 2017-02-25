#include "hw_port.h"
#include "pwm.h"
#include "tx_timer.h"

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