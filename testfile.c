#include <stdint.h>

typedef struct { } tx_protocol;
typedef struct { } hw_port;

typedef struct ps_details {
    const uint16_t hdr_time_a;
    const uint16_t hdr_time_b;
    const uint16_t pulse_one;
    const uint16_t space_one;
    const uint16_t pulse_zero;
    const uint16_t space_zero;
    const uint16_t tail;
    const uint8_t bit_cnt;
    const tx_protocol* protocol;
} ps_details;

typedef struct ntarget_dev {
    const char* name;
    const uint16_t address;
    const hw_port* port;
    const ps_details ps_data;
} ntarget_dev;

hw_port tx_usb;

int main(void) {
  
    ntarget_dev dvb_srv = {
        //Name         //Adress   //port    //ha  //hb
         "DVB-Server", 0xABCD,    &tx_usb,    0x1234,    0x6678 
    };
    uint16_t x = dvb_srv.ps_data.hdr_time_a;
    const ps_details pd  = dvb_srv.ps_data;

    
}