#include "ESP01.h"

#define ESP_EN(x)                   ((x) ? (DL_GPIO_setPins(OTHER_PORT, OTHER_ESP_EN_PIN))  : (DL_GPIO_clearPins(OTHER_PORT, OTHER_ESP_EN_PIN)))
#define ESP_RST(x)                   ((x) ? (DL_GPIO_setPins(OTHER_PORT, OTHER_ESP_RST_PIN))  : (DL_GPIO_clearPins(OTHER_PORT, OTHER_ESP_RST_PIN)))
oscilloscope_struct  oscilloscope;      

void esp01_sendAt(uint8_t* data){
    uint8_t i = 0;
    do{
        DL_UART_transmitData(ESP01_INST,data[i++]);
        while (DL_UART_isBusy(ESP01_INST));
    }while(!(data[i-1]==0x0A&&data[i]==0x00));
}

void esp01_sendData(uint8_t* data,uint8_t len){
    uint8_t i = 0;
    while (i!=len) {
        DL_UART_transmitData(ESP01_INST,data[i++]);
        while (DL_UART_isBusy(ESP01_INST));
    }
}

void esp01_init(const char*ssid,const char*password,const char*ip,const char*port){
    ESP_EN(1);
    system_delay_ms(120);
    ESP_RST(0);
    system_delay_ms(10);
    ESP_RST(1);
    system_delay_ms(1000);

    uint8_t connect_at[128];
    snprintf((char*)connect_at, sizeof(connect_at), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    esp01_sendAt(connect_at);
    system_delay_ms(10000);

    uint8_t udp_at[128];
    snprintf((char*)udp_at, sizeof(udp_at), "AT+CIPSTART=\"UDP\",\"%s\",%s,8080\r\n", ip, port);
    esp01_sendAt(udp_at);
    system_delay_ms(10000);
}
void esp01_start(){
    uint8_t tt_at[16];
    uint8_t tt_at2[16];
    snprintf((char*)tt_at, sizeof(tt_at), "AT+CIPMODE=1\r\n");   
    esp01_sendAt(tt_at);
    system_delay_ms(500);
    snprintf((char*)tt_at2, sizeof(tt_at2), "AT+CIPSEND\r\n");
    esp01_sendAt(tt_at2);
    system_delay_ms(500);
    esp01_sendData((uint8_t*)"Ready to transmit data!",23);
}

void esp01_close(){
    esp01_sendData((uint8_t*)"+++",3);
}

uint8_t oscilloscope_sum(uint8_t* buffer,uint8_t length){
    uint8_t temp_sum = 0;
    while(length--)
        temp_sum += *buffer++;
    return temp_sum;
}

void elsp01_oscilloscope_send(){

    oscilloscope.head = 0xAA;

    oscilloscope.channel_num &= 0x0f;

    oscilloscope.length = sizeof(oscilloscope_struct) - (8 - oscilloscope.channel_num) * 4;
    
    oscilloscope.channel_num |= 0x10;

    oscilloscope.check_sum   = 0;
    oscilloscope.check_sum   = oscilloscope_sum((uint8_t *)&oscilloscope, oscilloscope.length);

    esp01_sendData((uint8_t *)&oscilloscope,oscilloscope.length);
}