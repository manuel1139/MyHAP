/* 
 * File:   t_test.h
 * Author: manuel
 *
 * Created on 3. März 2017, 10:17
 */

#ifndef T_TEST_H
#define	T_TEST_H

#include "dev_ps.h"
#include "hw_ir.h"
#include "haapi.h"

const struct ps_details pt = {
    0x3504, //header_a
    0x19CD, //header_b
    0x0392, //a_1
    0x029B, //b_1
    0x0394, //a_0
    0x0914, //b_0
    0, //tail
    2,
    &hw_ir
};

struct my_target {
    struct target_dev d;
    struct ps_details pt1;
    struct ps_details pt2;
};

struct target_dev ps_dev = {
    "TestDev",
    0,     //address
    &tx_pulse_space,
    &rx_pulse_space
    
 };

#endif	/* T_TEST_H */

