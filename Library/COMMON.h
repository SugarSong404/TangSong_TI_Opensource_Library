#ifndef COMMON_H
#define COMMON_H

#include "ti_msp_dl_config.h"

#include "/Basic/TFT180.h"
#include "/Basic/TFT350.h"
#include "/Basic/ICM20602.h"
#include "/Basic/OpenMv.h"

#include "/ti/eeprom/emulation_type_b/eeprom_emulation_type_b.h"

typedef enum
{
    WHITE    = (0xFFFF),                                                     // 白色
    BLACK    = (0x0000),                                                     // 黑色
    BLUE     = (0x001F),                                                     // 蓝色
    PURPLE   = (0xF81F),                                                     // 紫色
    PINK     = (0xFE19),                                                     // 粉色
    RED      = (0xF800),                                                     // 红色
    MAGENTA  = (0xF81F),                                                     // 品红
    GREEN    = (0x07E0),                                                     // 绿色
    CYAN     = (0x07FF),                                                     // 青色
    YELLOW   = (0xFFE0),                                                     // 黄色
    BROWN    = (0xBC40),                                                     // 棕色
    GRAY     = (0x8430),                                                     // 灰色
}color_enum;

extern const uint8_t ascii_font_8x16[][16];
int abs(int x);
void func_float_to_str(char *str, float number, uint8_t point_bit);

#define system_delay_ms(m)    delay_cycles((m*32000))




#endif