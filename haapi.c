#include <stdint.h>

#include "haapi.h"
#include "target_dev.h"
#include "io_control.h"


void SendCommand(struct target_dev *d, uint16_t code) {
    send_cmd(d, code);
}

