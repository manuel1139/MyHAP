/* 
 * File:   hw_usb.h
 * Author: manuel
 *
 * Created on 24. Februar 2017, 17:27
 */

#ifndef HW_USB_H
#define	HW_USB_H

#include "hw_port.h"

void usb_send();
void usb_init();
void usb_cleanup();

hw_port hw_usb = {
    usb_init,
    usb_cleanup,            
    usb_send,

#endif	/* HW_USB_H */

