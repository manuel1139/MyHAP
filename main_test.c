#include <xc.h>

#include "system.h"

#include "haapi.h"

#include "yamaha.h"
#include "io_control.h"


void putch(unsigned char data) {
    while (!PIR1bits.TXIF) // wait until the transmitter is ready
        continue;
    TXREG = data; // send one character
}

void init_uart(void) {
    TXSTAbits.TXEN = 1; // enable transmitter
    RCSTAbits.SPEN = 1; // enable serial port
}

int main(void) {

    SYSTEM_Initialize();
    init_uart();

    SendCommand((dev_target*) & yamaha, Y_VOL_DOWN);
    //yamaha.dev.send_bus((struct device*) &yamaha, 0xABCD);

    while (1);

    return 0;
}


void high_priority interrupt high_isr(void) {

    TransmitISR();

}

