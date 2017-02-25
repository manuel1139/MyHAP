/* 
 * File:   tx_pulse_space.h
 * Author: manuel
 *
 * Created on 16. Februar 2017, 14:37
 */
#ifndef TX_RC5_H
#define	TX_RC5_H

#include <stdint.h>

#include "tx_protocol.h"
#include "target_dev.h"

void tx_rc5(struct target_dev*, uint16_t);

tx_protocol rc5 = { 
    tx_rc5,
};

#endif	/* TX_RC5_H */

