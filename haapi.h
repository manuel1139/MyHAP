/* 
 * File:   hidapi.h
 * Author: manuel
 *
 * Created on 17. Februar 2017, 23:36
 */

#ifndef HAAPI_H
#define	HAAPI_H

#include <stdint.h>

#include "target_dev.h"
#include "io_control.h"


void tx_usb(struct target_dev*, uint16_t);
void rx_pulse_space(struct ps_dev* r, uint16_t bit_time) {
void tx_rc5(struct target_dev*, uint16_t);

void tx_pulse_space(const struct ps_dev* r, uint16_t code);

void SendCommand(struct target_dev *d, uint16_t code);
void StartIRReceiver();

#endif	/* HAAPI_H */

