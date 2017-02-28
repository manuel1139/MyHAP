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


void SendCommand(struct target_dev *d, uint16_t code);
void StartIRReceiver();

#endif	/* HAAPI_H */

