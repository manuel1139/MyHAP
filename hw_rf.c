#include <xc.h>

#include "hw_port.h"
#include "system.h"
#include "timer_tx.h"
#include "pwm.h"

void rf_send() {
    RF_OUT = RF_OUT ^ 1;
}

void rf_init() {
    RF_OUT = 0; //act high --> todo: to target_dev
    OpenTxTimer();
}

void rf_cleanup() {
    RF_OUT = 0;
    CloseTxTimer();
}