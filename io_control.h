/* 
 * File:   control.h
 * Author: manuel
 *
 * Created on 22. Februar 2017, 22:33
 */

#ifndef CONTROL_H
#define	CONTROL_H

#include <stdint.h>
#include <stdbool.h>

#include "haapi.h"

void TransmitISR();
void ReceiveISR();

void io_ctrl_send_cmd(dev_ps*, code);



#endif	/* CONTROL_H */

