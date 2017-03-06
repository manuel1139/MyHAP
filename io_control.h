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

#define U2T(x) x*3/2    //us to ticks @12Mhz IC
#define T2U(x) x*2/3    //us to ticks @12Mhz IC

void TransmitISR();
void ReceiveISR();

void io_ctrl_send_cmd(dev_ps*, code);
void evdone(struct dev_ps* dt);


#endif	/* CONTROL_H */

