/* 
 * File:   tx_protocol.h
 * Author: manuel
 *
 * Created on 23. Februar 2017, 11:13
 */

#ifndef TX_PROTOCOL_H
#define	TX_PROTOCOL_H

typedef struct {
    void (*tx)(struct target_dev* target, uint16_t);
} tx_protocol;

#endif	/* TX_PROTOCOL_H */

