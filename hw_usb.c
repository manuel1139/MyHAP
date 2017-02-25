#include "hw_usb.h"
#include "system.h"


void usb_send() {
    if (!HIDTxHandleBusy(USBInHandle)) {

        ToSendDataBuffer[7] = 0xC0;
        ToSendDataBuffer[6] = 0xD1;
        ToSendDataBuffer[5] = ;
        ToSendDataBuffer[4] = ;

        ToSendDataBuffer[3] = C0;
        ToSendDataBuffer[2] = D1;
        ToSendDataBuffer[1] = (uint8_t) remotes[i]->rx_data.code_found;
        ToSendDataBuffer[0] = remotes[i]->rx_data.code_found >> 8;

        USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*) & ToSendDataBuffer[0], 32);
    }
}

void usb_init() {


}

void usb_cleanup() {

}