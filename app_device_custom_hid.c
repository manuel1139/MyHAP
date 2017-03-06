#include "usb.h"
#include "usb_device_hid.h"

#include <string.h>

#include "system.h"
#include "haapi.h"

unsigned char ReceivedDataBuffer[64] @ HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
unsigned char ToSendDataBuffer[64] @ HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;

volatile USB_HANDLE USBOutHandle;
volatile USB_HANDLE USBInHandle;

void APP_DeviceCustomHIDInitialize() {
    //initialize the variable holding the handle for the last
    // transmission
    USBInHandle = 0;

    //enable the HID endpoint
    USBEnableEndpoint(CUSTOM_DEVICE_HID_EP, USB_IN_ENABLED |
            USB_OUT_ENABLED |
            USB_HANDSHAKE_ENABLED |
            USB_DISALLOW_SETUP);

    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = (volatile USB_HANDLE)HIDRxPacket(CUSTOM_DEVICE_HID_EP,
            (uint8_t*) & ReceivedDataBuffer, 64);
}

void HIDSend(code command) {
    
    if (USBGetDeviceState() < CONFIGURED_STATE) {
        /* Jump back to the top of the while loop. */
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if (USBIsDeviceSuspended() == true) {
        /* Jump back to the top of the while loop. */
        return;
    }

    if (!HIDTxHandleBusy(USBInHandle)) {
        uint16_t* ptrSB = (uint16_t*) & ToSendDataBuffer[0];
        *ptrSB = command;
        ToSendDataBuffer[7] = 0;
        ToSendDataBuffer[6] = 0;
        ToSendDataBuffer[5] = (uint8_t) command;
        ToSendDataBuffer[4] = command >> 8;

        ToSendDataBuffer[3] = 0;
        ToSendDataBuffer[2] = 0;
        ToSendDataBuffer[1] = (uint8_t) command;
        ToSendDataBuffer[0] = command >> 8;

        USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*) & ToSendDataBuffer[0], 32);
    }

}

void APP_DeviceCustomHIDTasks() {
    uint16_t command;
    if (HIDRxHandleBusy(USBOutHandle) == false) {
        //We just received a packet of data from the USB host.
        command = ReceivedDataBuffer[0] << 8;
        command |= ReceivedDataBuffer[1];

        //Re-arm the OUT endpoint, so we can receive the next OUT data packet 
        //that the host may try to send us.
        USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*) & ReceivedDataBuffer, 64);
    }
}