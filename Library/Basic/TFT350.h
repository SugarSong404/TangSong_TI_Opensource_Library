#ifndef TFT_350_H
#define TFT_350_H
#include "../COMMON.h"

static uint16_t           tft350_pencolor     = 0x001F;
static uint16_t           tft350_bgcolor      = 0xFFFF;
static uint16_t            tft350_x_max        = 480;
static uint16_t            tft350_y_max        = 320;

void tft350_init (void);
void tft350_clear_color (uint16_t tft350_bgcolor);
void tft350_show_string_color (uint16_t x, uint16_t y, const char dat[],uint16_t tft350_bgcolor,uint16_t tft350_pencolor);
void tft350_show_num_color (uint16_t x, uint16_t y, const float dat, uint8_t num, uint8_t pointnum,uint16_t tft350_bgcolor,uint16_t tft350_pencolor);
void tft350_draw_point_color (uint16_t x, uint16_t y, const uint16_t color);
void tft350_show_image (uint16_t x, uint16_t y, const uint16_t *image, uint16_t width, uint16_t height);
#define tft350_clear()                            (tft350_clear_color(tft350_bgcolor))
#define tft350_show_string(x,y,dat)                 (tft350_show_string_color((x),(y),(dat),tft350_bgcolor,tft350_pencolor))
#define tft350_show_float(x,y,dat,num,pointnum)       (tft350_show_num_color((x),(y),(dat),(num),(pointnum),tft350_bgcolor,tft350_pencolor))
#define tft350_show_int(x,y,dat,num)       (tft350_show_num_color((x),(y),(dat),(num),0,tft350_bgcolor,tft350_pencolor))


#endif