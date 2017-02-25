#include <xc.h>
#include "usb.h"
#include "usb_device_hid.h"

#include "app_device_custom_hid.h"
#include "tx_usb.h"
#include "target_dev.h"

void tx_usb(struct target_dev*, uint16_t command) {

    HIDSend(command);

}