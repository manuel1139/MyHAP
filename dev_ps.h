/* 
 * File:   dev_ps.h
 * Author: manuel
 *
 * Created on 27. Februar 2017, 17:55
 */

#ifndef DEV_PS_H
#define	DEV_PS_H

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

#endif	/* DEV_PS_H */

