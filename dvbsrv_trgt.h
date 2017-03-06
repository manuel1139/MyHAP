/* 
 * File:   dvbsrv_trgt.h
 * Author: manuel
 *
 * Created on 6. März 2017, 10:55
 */

#ifndef DVBSRV_TRGT_H
#define	DVBSRV_TRGT_H

#include "haapi.h"

remote dvbsrv_trgt = {
    "DVB Server",
    0x0,
    &send_usb
}
#endif	/* DVBSRV_TRGT_H */

