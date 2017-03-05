#include <stdint.h>

#include "haapi.h"
#include "io_control.h"
#include "app_device_custom_hid.h"


void send_ps(dev_target* td, code c) {
    dev_ps* d = (dev_ps*) td;
    io_ctrl_send_cmd(d, c);
}

void send_usb(device* d, code command) {
    HIDSend(command);
}

void SendCommand(dev_target *d, code code) {
    //    d->protocol->tx(d, code);
    d->send_bus(d, code);
}

