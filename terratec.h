/* 
 * File:   terratec.h
 * Author: manuel
 *
 * Created on 6. März 2017, 10:46
 */

#ifndef TERRATEC_H
#define	TERRATEC_H

#define KEY_1 0x40BF
#define KEY_2 0xC03F
#define KEY_3 0x20DF
#define KEY_4 0xA05F
#define KEY_5 0x609F
#define KEY_6 0xE01F
#define KEY_7 0x10EF
#define KEY_8 0x906F
#define KEY_9 0x50AF
#define KEY_0 0x30CF

const uint16_t terratec_ir_rc_codes[] = {
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5,
    KEY_6, KEY_7, KEY_8, KEY_9
};

device terratec = {
    "Terratec",
#if 0
    0x3575, //header_a
    0x199C, //header_b
    0x0385,
    0x08E5,
    0x03BD, //low
    0x026F, //high
    0, //tail
    0x28D7, //pre_code
    32,
    &init_rx,
    &init_tx,
    &ir_rx_pulse_space, //rx_func
    0, //tx_func
    &terratec_ir_rc_codes[0],
    idle
#endif
}; 

#endif	/* TERRATEC_H */

