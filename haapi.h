/* 
 * File:   hidapi.h
 * Author: manuel
 *
 * Created on 17. Februar 2017, 23:36
 */

#ifndef HAAPI_H
#define	HAAPI_H

#include <stdint.h>

#include "hw_port.h"
#include "app_device_custom_hid.h"

typedef const uint16_t address;
typedef const uint16_t code;

typedef const uint16_t time_val;

typedef const uint16_t pulse;
typedef const uint16_t space;

typedef struct ps {
    pulse pulse;
    space space;
} ps;

typedef struct command {
    address addr;
    code code;
} command;

typedef struct device {
    const char *name;
    address addr;
} device;


typedef struct dev_src {
    device dev;
    void (*recv_bus)(device*, time_val);
} dev_src;

typedef struct dev_target {
    device dev;
    void (*send_bus)(struct dev_target*, code);
} dev_target;

typedef struct dev_ps {
    dev_target devtrgt;
    ps header;
    ps zero;
    ps one;
    pulse tail;
    uint8_t bit_cnt;
    const hw_port* hw_port;
    void (*tx_prot)(struct dev_ps*, code);
} dev_ps;

//samsung protocol
typedef struct dev_samsung {
    dev_target dev;
    ps header;
    ps zero;
    ps one;
    ps sync;
    pulse stop;
    uint8_t bit_cnt_address;
    uint8_t bit_cnt_code;
    const hw_port* hw_port;
    void (*tx_prot)(dev_ps*, code);
} dev_samsung;

void send_ps(dev_target*, code);
void send_rc5(dev_target*, code);
void send_horizon(dev_target*, code);
void send_usb(dev_target*, code);

void tx_ps(dev_ps*, code);
void HIDSend(code);
#if 0

void rx_pulse_space(struct ps_dev* r, uint16_t bit_time);
void tx_rc5(struct target_dev*, uint16_t);
#endif 
void SendCommand(dev_target *d, code code);
void StartIRReceiver();

#endif	/* HAAPI_H */

