#include <xc.h>
#include "system.h"
#include "system_config.h"
#include "usb.h"
#include "usb_config.h"

void SYSTEM_Initialize(void)
{    
    ADCON1 = 0x0f;  //All PORTABits DIGITAL
 
    /*******************************************************************/
    // Enable System Interupts
    /*******************************************************************/
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    INTCONbits.PEIE = 1;
    
    RCONbits.IPEN = 1; //Interrupt priority
    
    IR_OUT = 0;
    IR_OUT_TRIS = OUTPUT_PIN;
        
    RF_OUT = 0;
    RF_OUT_TRIS = OUTPUT_PIN;

    LED1 = 0 ;
    LED1_TRIS = OUTPUT_PIN;
    
    LED2 = 0;
    LED2_TRIS = OUTPUT_PIN;
  
    DEAD_PIN_TRIS = INPUT_PIN;
       
}

