#include "usb.h"
#include "usb_device_hid.h"

#include <string.h>

#include "system.h"

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

void APP_DeviceCustomHIDTasks() {
#if 0    
    extern struct remote * remotes[];
    for (int i = 0; remotes[i]; i++) {
        if (remotes[i]->rx_data.code_found != 0) {
            if (!HIDTxHandleBusy(USBInHandle)) {
                LED1 = 1;
                ToSendDataBuffer[7] = 0;
                ToSendDataBuffer[6] = 0;
                ToSendDataBuffer[5] = (uint8_t) remotes[i]->rx_data.code_found;
                ToSendDataBuffer[4] = remotes[i]->rx_data.code_found >> 8;

                ToSendDataBuffer[3] = 0;
                ToSendDataBuffer[2] = 0;
                ToSendDataBuffer[1] = (uint8_t) remotes[i]->rx_data.code_found;
                ToSendDataBuffer[0] = remotes[i]->rx_data.code_found >> 8;

                USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*) & ToSendDataBuffer[0], 32);
                remotes[i]->rx_data.code_found = 0;
                LED1 = 0;
            }
        }
    }
#endif    
}
