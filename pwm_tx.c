/****************************************************************
 * PWM registers configuration
 * Fosc = 48000000 Hz
 * Fpwm = 37974.68 Hz (Requested : 38000 Hz)
 * Duty Cycle = 50 %
 * Resolution is 10 bits
 * Prescaler is 4
 * Used Resources: 
 * TIMER2
 * CCP
 ***************************************************************/
#include <xc.h>

#include "pwm.h"
#include "system.h"

void OpenPWM() {
    //PR2 frequency and resolution
    PR2 = 0x4E; 
    
    //T2CON ? PS3 PS2 PS1 PS0 TMR2ON CKPS1 CKPS0 pre & postscaler enable
    T2CON = 0b00000101;

    CCPR2L = 0b00100111;
    
    //reset PWM
    CCP2CON = 0b00010000;
}

void StartPWM() {
    //PWM Mode
    CCP2CONbits.CCP2M = 0xC;
}

void StopPWM() {
    //diasble pwm
    CCP2CONbits.CCP2M = 0;
}

void TogglePWM() {
    if (CCP2CONbits.CCP2M == 0xC) {
        CCP2CONbits.CCP2M = 0;
    } else {
        CCP2CONbits.CCP2M = 0xC;
    }
}

void ClosePWM() {
    CCP2CONbits.CCP2M = 0;
}

