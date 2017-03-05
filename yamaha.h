/* 
 * File:   yamaha.h
 * Author: manuel
 *
 * Created on 5. März 2017, 12:49
 */

#ifndef YAMAHA_H
#define	YAMAHA_H

#include "haapi.h"
#include "hw_ir.h"

//remote keys
#define Y_VOL_UP 0xA758
#define Y_VOL_DOWN 0x27D8

dev_ps yamaha = {
    "Yamaha RCV",
    0xA15E,
    &send_ps,
    9000,   //us header pulse
    4500,   //us header space
    640,    //us zero pulse
    1600,    //us zero space
    640,    //us one pulse
    470,    //us one space
    470,    //us tail
    32,     //bit count
    &hw_ir, //ir 
    &tx_ps  //protocol 
};

#endif	/* YAMAHA_H */

