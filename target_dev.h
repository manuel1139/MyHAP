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

typedef struct ps_details {
    const uint16_t hdr_time_a;
    const uint16_t hdr_time_b;
    const uint16_t pulse_one;
    const uint16_t space_one;
    const uint16_t pulse_zero;
    const uint16_t space_zero;
    const uint16_t tail;
    const uint8_t bit_cnt;
    const hw_port* port;
} ps_details;

typedef struct target_dev {
    const char* name;
    const uint16_t address;
    const tx_protocol* protocol;
    const ps_details* ps_data;
    void (*send_bus)(struct target_dev*, uint16_t);
} target_dev;

#endif	/* TARGET_DEV_H */
