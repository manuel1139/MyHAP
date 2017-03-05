/* 
 * File:   horizon.h
 * Author: manuel
 *
 * Created on 5. März 2017, 12:48
 */

#ifndef HORIZON_H
#define	HORIZON_H

#include "haapi.h"
#include "hw_ir.h"

dev_samsung horizon = {
    "Horizon Box",
    0x0,
    &send_horizon,
    4500,
    4500,
    550,
    550,
    550,
    1650,
    550,
    4500,
    550,
    16,
    20,
    &hw_ir,
};


#endif	/* HORIZON_H */

