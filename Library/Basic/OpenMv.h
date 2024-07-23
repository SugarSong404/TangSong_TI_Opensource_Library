#ifndef OPENMV_H
#define OPENMV_H
#include "../COMMON.h"

#define SELF_CHECK_CMD 0x1A
#define STOP_CMD 0x1C
#define TIME_OUT 0xFF
#define END1 0x01
#define END2 0xFE
#define END3 0xFF

uint8_t openmv_init();
void openmv_cmd(uint8_t cmd , uint8_t (*func)(uint8_t*));
float openmv_parse_float(uint8_t* data,uint8_t* index);
int openmv_parse_int(uint8_t* data, uint8_t* index);
const char* openmv_parse_string(uint8_t* data, uint8_t* index);
uint8_t openmv_parse_byte(uint8_t* data, uint8_t* index);

#define OMB(d,i) openmv_parse_byte((data),&(i))
#define OMF(d,i) openmv_parse_float((data),&(i))
#define OMI(d,i) openmv_parse_int((data),&(i))
#define OMS(d,i) openmv_parse_string((data),&(i))

#endif