/* 
 * File:   tx_pulse_space.h
 * Author: manuel
 *
 * Created on 16. Februar 2017, 14:37
 */
#ifndef TX_PULSE_SPACE_H
#define	TX_PULSE_SPACE_H

#include "tx_protocol.h"
#include "target_dev.h"

void tx_pulse_space(struct target_dev*, uint16_t);
extern void send(struct target_dev*, uint16_t);
void ps_init();
void ps_close();

tx_protocol pulse_space = { 
    tx_pulse_space,
};


#endif	/* TX_PULSE_SPACE_H */

