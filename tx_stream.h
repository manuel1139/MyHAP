/* 
 * File:   tx_stream.h
 * Author: manuel
 *
 * Created on 17. Februar 2017, 11:26
 */

#ifndef TX_STREAM_H
#define	TX_STREAM_H

#include <stdint.h>
#include <stdbool.h>

void evdone(struct target_dev* r);
void TransmitISR();

typedef struct {
    void (*tx)(struct target_dev* target, uint16_t);
    void (*send)(struct target_dev* target, uint16_t);
    
    struct target_dev* target;
    bool busy;
    
    //static void TransmitISR();
} tx_stream;

#endif	/* TX_STREAM_H */

