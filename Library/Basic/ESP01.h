#ifndef ESP01_H
#define ESP01_H
#include "../COMMON.h"

typedef struct
{
    uint8_t head;                               
    uint8_t channel_num;                              
    uint8_t check_sum;                                
    uint8_t length;                                             
    float data[8];
}oscilloscope_struct;

void esp01_init(const char*ssid,const char*password,const char*ip,const char*port);
void esp01_start();
void esp01_close();
void esp01_sendData(uint8_t* data,uint8_t len);
void esp01_sendAt(uint8_t* data);
void elsp01_oscilloscope_send();

#define esp01_oscilloscope_channel(i,a) {oscilloscope.data[i] = a;\
    oscilloscope.channel_num = (oscilloscope.channel_num>((i+1)|0x10))?(oscilloscope.channel_num):(i+1);\
}
extern oscilloscope_struct  oscilloscope;      
#endif