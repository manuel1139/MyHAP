#include <stdint.h>

#include "haapi.h"
#include "target_dev.h"
#include "io_control.h"

#include "app_device_custom_hid.h"

void send_ps(struct target_dev* d, uint16_t command) {
    io_ctrl_send_cmd(d, command);
}

void send_usb(struct target_dev* d, uint16_t command) {
    HIDSend(command);
}

void SendCommand(struct target_dev *d, uint16_t code) {
    //    d->protocol->tx(d, code);
    d->send_bus(d, code);
}

