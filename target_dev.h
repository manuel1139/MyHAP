/* 
 * File:   target_dev.h
 * Author: manuel
 *
 * Created on 17. Februar 2017, 12:13
 */

#ifndef TARGET_DEV_H
#define	TARGET_DEV_H

#include <stdint.h>

#include "tx_protocol.h"
#include "hw_port.h"
#include "dev_ps.h"

typedef struct target_dev {
    const char* name;
    const uint16_t address;
    //const tx_protocol* protocol;
    void (*tx_func)(struct target_dev*, uint16_t);
    const ps_details* ps_data;
    void (*send_bus)(struct target_dev*, uint16_t);
    void (*recv_bus)(struct target_dev*, uint16_t);
} target_dev;



#endif	/* TARGET_DEV_H */
