/* 
 * File:   t_yamaha.h
 * Author: manuel
 *
 * Created on 17. Februar 2017, 22:44
 */

#include "tx_pulse_space.h"
#include "io_control.h"
#include "hw_ir.h"
#include "target_dev.h"

#ifndef T_YAMAHA_H
#define	T_YAMAHA_H

//remote keys
#define Y_VOL_UP 0xA758
#define Y_VOL_DOWN 0x27D8



const struct ps_details p = {
    0x3504, //header_a
    0x19CD, //header_b
    0x0392, //a_1
    0x029B, //b_1
    0x0394, //a_0
    0x0914, //b_0
    0, //tail
    32,
    &hw_ir
};

struct target_dev yamaha = {
    "Yamaha RCV",
    0xFF08,     //address
    &rx_pulse_space,
    &p,
    send_ps,
    rx_pulse_space
 };


#endif	/* T_YAMAHA_H */

