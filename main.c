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

#include "t_pollin.h"
#include "t_minfinity.h"

/*
 * 
 * for debugging purposes todo: ifdef 
void putch(unsigned char data) {
    while (!PIR1bits.TXIF) // wait until the transmitter is ready
        continue;
    TXREG = data; // send one character
}

void init_uart(void) {
    TXSTAbits.TXEN = 1; // enable transmitter
    RCSTAbits.SPEN = 1; // enable serial port
}
 */

int main(void) {

    SYSTEM_Initialize();

    //init_uart();
    //rintf("starting\n");

    USBDeviceInit();
    USBDeviceAttach();

    cmd_target dvb_srv = {
        //Name           //Adress     //port
        { "DVB-Server", 0xABCD, &tx_usb}
    };

    /*
    cmd_target targets[0] = {
       //Name           //Adress     //port
        { "DVB-Server", 0xABCD,      &hw_usb}
    };
     */

    //setup receiving hardware and start receiving/decoding
    StartIRReceiver();
    //io_control->StartIrReceiver())

    while (1) {
        static uint32_t cntr = 0;
        if (cntr++ > 100000ul) {
            SendCommand(&dvb_srv, S3_ON);
            SendCommand(&pollin_rf_rc, S3_ON);
            LED1 = LATAbits.LA5;
            LED2 = LATAbits.LA5;
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

void high_priority interrupt high_isr(void) {

    USBDeviceTasks();

    //    ReceiveISR();

    TransmitISR();

}

