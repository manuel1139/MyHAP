/* 
 * File:   t_horizon.h
 * Author: manuel
 *
 * Created on 3. März 2017, 20:12
 */

#ifndef T_HORIZON_H
#define	T_HORIZON_H


const struct ps_details p_h_1 = {
    0x19CD, //header_a
    0x19CD, //header_b
    0x0372, //a_1
    0x0217, //b_1
    0x034D, //a_0
    0x07EF, //b_0
    0x0, //tail
    16,
    &hw_ir
};

const struct ps_details p_h_2 = {
    0x3504, //header_a
    0x19CD, //header_b
    0x0392, //a_1
    0x029B, //b_1
    0x0394, //a_0
    0x0914, //b_0
    0x0392, //tail
    32,
    &hw_ir
};


struct target_dev horizon = {
    "Horizon",
    0x0,     //address
    tx_pulse_space,
    &p,
    send_ps,
    rx_pulse_space
 };

#endif	/* T_HORIZON_H */

