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

void TransmitISR();
void io_ctrl_send_cmd(struct target_dev *d, uint16_t code);

#endif	/* CONTROL_H */

