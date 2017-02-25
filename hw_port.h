/* 
 * File:   hw_pic.h
 * Author: manuel
 *
 * Created on 17. Februar 2017, 22:37
 */

#ifndef HW_PORT_H
#define	HW_PORT_H

typedef struct hw_port {
    void (*init)();
    void (*cleanup)();
    void (*send)();
} hw_port;

#endif	/* HW_PORT_H */

