/* 
 * File:   tx_usb.h
 * Author: manuel
 *
 * Created on 25. Februar 2017, 14:00
 */

#ifndef TX_USB_H
#define	TX_USB_H

#include <stdint.h>

#include "tx_protocol.h"
#include "target_dev.h"

void tx_usb(struct target_dev*, uint16_t);

tx_protocol usb_d = { 
    tx_usb,
//    isExclusive,
//    0
};


#endif	/* TX_USB_H */

