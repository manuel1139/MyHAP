/* 
 * File:   hw_rf.h
 * Author: manuel
 *
 * Created on 18. Februar 2017, 12:09
 */

#ifndef HW_RF_H
#define	HW_RF_H

#include "hw_port.h"

void rf_send();
void rf_init();
void rf_cleanup();

hw_port hw_rf = {
    rf_init,
    rf_cleanup,            
    rf_send,
};

#endif	/* HW_RF_H */

