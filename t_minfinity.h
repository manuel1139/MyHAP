/* 
 * File:   minfinity.h
 * Author: manuel
 *
 * Created on 17. Februar 2017, 21:04
 */

#ifndef MINFINITY_H
#define	MINFINITY_H

#include "target_dev.h"
#include "tx_pulse_space.h"
#include "hw_rf.h"
#include "hw_usb.h"

#if 0
target_dev minf = {
    //name addr  port // 
    { "RF Switch/Dimmer", 0xFF08, &tx_usb }
}

typedef struct {
    const uint16_t hdr_time_a;
    const uint16_t hdr_time_b;
    const uint16_t pulse_one;
    const uint16_t space_one;
    const uint16_t pulse_zero;
    const uint16_t space_zero;
    const uint16_t tail;
    const uint8_t bit_cnt;
    const tx_protocol* protocol;
} ps_details;

typedef struct  {
    char_target target;
    ps_details ps_data;
};
target_dev minfinity = {
    "Minfiny RF Switches & Dimmers",
    0x3504, //header_a
    0x19CD, //header_b
    0x0392, //a_1
    0x029B, //b_1
    0x0394, //a_0
    0x0914, //b_0
    0, //tail
    0xFF08,     //address
    32,
    &pulse_space,
    &hw_rf            
 };
#endif

#endif	/* MINFINITY_H */

