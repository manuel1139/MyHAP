/*
 *
 * by Manuel Kampert (manuel.kampert@googlemail.com)
 *  
 * Used peripherals
 * 
 * CCP1,TMR1 receiving IR data
 * 
 * TMR0 for transmitting RF data 
 * 
 * TMR2 for PWM and transmitting IR data @ 38khz
 * 
 */

#include <xc.h>
#include <stdbool.h>       /* For true/false definition */
#include <stdint.h>        /* For uint8_t definition */

#include "system.h"

#include "usb.h"
#include "usb_device_hid.h"

#include "app_device_custom_hid.h"

#include "haapi.h"

#include "terratec.h"
#include "yamaha.h"


//#define DEBUG
#ifdef DEBUG

/*
 * for debugging purposes todo: ifdef  
 */

void putch(unsigned char data) {
    while (!PIR1bits.TXIF) // wait until the transmitter is ready
        continue;
    TXREG = data; // send one character
}

void init_uart(void) {
    TXSTAbits.TXEN = 1; // enable transmitter
    RCSTAbits.SPEN = 1; // enable serial port
}
#endif

//remotes that receive commands
remote *remotes[] = {
    &terratec,
    NULL
};

cmd2target c2t_list[] = {
    { 0x28D7, KEY_1, (dev_target*) & yamaha},
    { NULL}
};

SendTarget(command cmd) {

    for (int i = 0; c2t_list[i].cmd.addr; i++) {
        if ((cmd.addr == c2t_list[i].cmd.addr) &&
                (cmd.code == c2t_list[i].cmd.code)) {
            c2t_list[i].target->send_bus(c2t_list[i], Y_VOL_UP);
        }
    }
}

int main(void) {

    SYSTEM_Initialize();

    //init_uart();
    //printf("starting\n");

    USBDeviceInit();
    USBDeviceAttach();

    //setup receiving hardware and start receiving/decoding
    StartIRReceiver();

    command cmd;

    while (1) {

        //check each remote for new commands
        for (int i = 0; remotes[i]; i++) {
            if (remotes[i]->code_received) {
                cmd.addr = remotes[i]->dev.addr;
                cmd.code = remotes[i]->code_received;
                SendTarget(cmd);
            }
        }
    }
}

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size) {
    switch ((int) event) {
        case EVENT_TRANSFER:
            break;

        case EVENT_SOF:
            /* We are using the SOF as a timer to time the LED indicator.  Call
             * the LED update function here. */
            //            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_SUSPEND:
            /* Update the LED status for the suspend event. */
            //            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_RESUME:
            /* Update the LED status for the resume event. */
            //            APP_LEDUpdateUSBStatus();
            break;

        case EVENT_CONFIGURED:
            /* When the device is configured, we can (re)initialize the demo
             * code. */
            APP_DeviceCustomHIDInitialize();
            break;

        case EVENT_SET_DESCRIPTOR:
            break;

        case EVENT_EP0_REQUEST:
            /* We have received a non-standard USB request.  The HID driver
             * needs to check to see if the request was for it. */
            USBCheckHIDRequest();
            break;

        case EVENT_BUS_ERROR:
            break;

        case EVENT_TRANSFER_TERMINATED:
            break;

        default:
            break;
    }
    return true;
}

extern TransmitISR();
extern ReceiveISR();

void high_priority interrupt high_isr(void) {

    USBDeviceTasks();

    ReceiveISR();

    TransmitISR();

}

