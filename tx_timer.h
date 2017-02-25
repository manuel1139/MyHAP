/* 
 * File:   tx_timer.h
 * Author: manuel
 *
 * Created on 20. Februar 2017, 08:15
 */
#ifndef TX_TIMER_H
#define	TX_TIMER_H

#include <stdint.h>

void OpenTxTimer();
void WriteTxTimer(uint16_t val);
void CloseTxTimer();

#endif	/* TX_TIMER_H */

