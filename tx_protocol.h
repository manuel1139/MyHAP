/* 
 * File:   tx_protocol.h
 * Author: manuel
 *
 * Created on 23. Februar 2017, 11:13
 */

#ifndef TX_PROTOCOL_H
#define	TX_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    void (*tx)(struct target_dev* target, uint16_t);
//    bool (*isExclusive)();
    
//    bool exclusive;
} tx_protocol;

#endif	/* TX_PROTOCOL_H */

