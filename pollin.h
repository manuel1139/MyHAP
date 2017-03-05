/* 
 * File:   pollin.h
 * Author: manuel
 *
 * Created on 19. Februar 2017, 01:35
 */

#ifndef POLLIN_H
#define	POLLIN_H

#include "haapi.h"
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


dev_ps yamaha = {
    "Pollin wall plugs",
    0x000B, //address
    &send_ps,
    0,   //us header pulse
    0x03F0,   //us header space
    0x043F,    //us zero pulse
    0x07B2,    //us zero space
    0x03C8,    //us one pulse
    0x0829,    //us one space
    0x0F00,    //tail
    20,     //bit count
    &hw_ir, //ir 
    &tx_ps  //protocol 
};

#endif	/* POLLIN_H */

