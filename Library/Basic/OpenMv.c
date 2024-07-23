#include "OpenMv.h"

uint8_t openmv_init(){
    DL_UART_transmitData(OPENMV_INST,SELF_CHECK_CMD);
    while (DL_UART_isBusy(OPENMV_INST));
    system_delay_ms(100);
    uint8_t data = 0;
    uint8_t time = 0;
    while (data != 0x1B) {
        if(time++ >= TIME_OUT)return 0;
        data = DL_UART_receiveDataBlocking(OPENMV_INST);
    }
    return 1;
}

void openmv_cmd(uint8_t cmd , uint8_t (*func)(uint8_t*)){
    DL_UART_transmitData(OPENMV_INST,cmd);
    while (DL_UART_isBusy(OPENMV_INST));
    system_delay_ms(100);
    uint8_t loop_flag = 1;
    uint8_t data[128];
    while (loop_flag){
        DL_UART_receiveDataBlocking(OPENMV_INST);
        uint8_t temp = DL_UART_receiveDataBlocking(OPENMV_INST);
        uint8_t last_temp = 0;
        uint8_t last_last_temp = 0;
        uint8_t i = 0;
        while (!(temp==END3&&last_temp==END2&&last_last_temp==END1)){
            data[i++] = temp;
            last_last_temp = last_temp;
            last_temp = temp;
            temp = DL_UART_receiveDataBlocking(OPENMV_INST);
        }
        loop_flag = func(data);
        system_delay_ms(50);
    } 
    DL_UART_transmitData(OPENMV_INST,STOP_CMD);
    while (DL_UART_isBusy(OPENMV_INST));
    system_delay_ms(100);
}
int openmv_parse_int(uint8_t* data, uint8_t* index) {
    int i = (int)(
        ((int32_t)data[*index]) |
        ((int32_t)data[*index + 1] << 8) |
        ((int32_t)data[*index + 2] << 16) |
        ((int32_t)data[*index + 3] << 24)
    );
    *index +=4;
    return i;
}
float openmv_parse_float(uint8_t* data,uint8_t* index){
    union {
        uint32_t i;
        float f;
    } u;

    u.i = ((uint32_t)data[*index]) |
          ((uint32_t)data[*index + 1] << 8) |
          ((uint32_t)data[*index + 2] << 16) |
          ((uint32_t)data[*index + 3] << 24);
    *index +=4;
    return u.f;
}
const char* openmv_parse_string(uint8_t* data, uint8_t* index) {
    const char* str = (const char*)(data + *index);
    uint8_t length = 0;
    while (data[*index + length] != '\0') {
        length++;
    }
    *index += length + 1;
    return str;
}
uint8_t openmv_parse_byte(uint8_t* data, uint8_t* index){
    *index+=1;
    return data[*index];
}