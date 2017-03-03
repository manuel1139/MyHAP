/* 
 * File:   t_test.h
 * Author: manuel
 *
 * Created on 3. März 2017, 10:17
 */

#ifndef T_TEST_H
#define	T_TEST_H

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


struct target_dev testd = {
    "Test RCV",
    0,     //address
    tx_pulse_space,
    &pt,
    send_ps,
    rx_pulse_space
 };

#endif	/* T_TEST_H */

