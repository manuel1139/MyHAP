/* 
 * File:   hw_ir.h
 * Author: manuel
 *
 * Created on 18. Februar 2017, 12:36
 */

#ifndef HW_IR_H
#define	HW_IR_H

#include "hw_port.h"

void ir_send();
void ir_init();
void ir_cleanup();

hw_port hw_ir = {
    ir_init,
    ir_cleanup,            
    ir_send,
};


#endif	/* HW_IR_H */

