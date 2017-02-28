/* 
 * File:   t_pollin.h
 * Author: manuel
 *
 * Created on 19. Februar 2017, 01:35
 */

#ifndef T_POLLIN_H
#define	T_POLLIN_H

#include "tx_pulse_space.h"
#include "hw_rf.h"

//Pollin RF Remote wall plugs and dimmers
#define S1_ON  0x0011
#define S1_OFF 0x0000
#define S2_ON  0x0093
#define S2_OFF 0x0082    
#define S3_ON  0x0050
#define S3_OFF 0x0041    
#define S4_ON  0x00D2
#define S4_OFF 0x00C3    
#define ALL_ON 0x00F0
#define ALL_OFF 0x00E1
#define DARK   0x001B
#define LIGHT  0x000A
#define STEST 0x80AB


const struct ps_details ps_pollin = {
    0x0, //header_a    
    0x03F0, //header_b
    0x043F, //pulse_one
    0x07B2, //space_one
    0x03C8, //pulse_zero
    0x0829, //space_zero
    0x0F00, //tail
    20,
    &hw_rf
};
    
struct target_dev pollin = {
    "Pollin wall plugs",
    0x000B, //address
    &tx_pulse_space,
    &ps_pollin,
    &send_ps
            
};

#endif	/* T_POLLIN_H */

