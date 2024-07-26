#include "TFT350.h"
#define TFT350_DC(x)                   ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_DC_PIN))  : (DL_GPIO_clearPins(TFT_PORT, TFT_DC_PIN)))
#define TFT350_RST(x)                  ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_RES_PIN)) : (DL_GPIO_clearPins(TFT_PORT, TFT_RES_PIN)))
#define TFT350_CS(x)                   ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_CS_PIN))  : (DL_GPIO_clearPins(TFT_PORT, TFT_CS_PIN)))
#define TFT350_BL(x)                   ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_BL_PIN))  : (DL_GPIO_clearPins(TFT_PORT, TFT_BL_PIN)))

void tft350_write_8bit_data (uint8_t data){
    DL_SPI_transmitData8  (TFT_SPI_INST, data);while (DL_SPI_isBusy(TFT_SPI_INST));
}
void tft350_write_16bit_data (uint16_t data){
    DL_SPI_transmitData8(TFT_SPI_INST, (uint8_t)((data>>8)&0xF8));while (DL_SPI_isBusy(TFT_SPI_INST));
    DL_SPI_transmitData8(TFT_SPI_INST, (uint8_t)((data>>3)&0xFC));while (DL_SPI_isBusy(TFT_SPI_INST));
    DL_SPI_transmitData8(TFT_SPI_INST, (uint8_t)(data<<3));while (DL_SPI_isBusy(TFT_SPI_INST));
}
static void tft350_write_index (uint8_t dat)
{
    TFT350_DC(0);
    tft350_write_8bit_data(dat);
    TFT350_DC(1);
}
static void tft350_set_region (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    tft350_write_index(0x2a);
    tft350_write_8bit_data(x1>>8);
    tft350_write_8bit_data(0x00FF&x1);
    tft350_write_8bit_data(x2>>8);
    tft350_write_8bit_data(0x00FF&x2);

    tft350_write_index(0x2b);
    tft350_write_8bit_data(y1>>8);
    tft350_write_8bit_data(0x00FF&y1);
    tft350_write_8bit_data(y2>>8);
    tft350_write_8bit_data(0x00FF&y2);
    tft350_write_index(0x2c);
}
void tft350_clear_color (uint16_t tft350_bgcolor)
{
    uint32_t i = tft350_x_max * tft350_y_max;

    TFT350_CS(0);
    tft350_set_region(0, 0, tft350_x_max - 1, tft350_y_max - 1);
    for( ; i!= 0; i --)
    {
        tft350_write_16bit_data(tft350_bgcolor);
    }
    TFT350_CS(1);
}
void tft350_init (void)
{
    TFT350_RST(0);
    system_delay_ms(10);
    TFT350_RST(1);
    system_delay_ms(120);
    TFT350_CS(0);
    
    tft350_write_index(0XF7);
    tft350_write_8bit_data(0xA9);
    tft350_write_8bit_data(0x51);
    tft350_write_8bit_data(0x2C);
    tft350_write_8bit_data(0x82);

    tft350_write_index(0xC0);
    tft350_write_8bit_data(0x11);
    tft350_write_8bit_data(0x09);

    tft350_write_index(0xC1);
    tft350_write_8bit_data(0x41);

    tft350_write_index(0XC5);
    tft350_write_8bit_data(0x00);
    tft350_write_8bit_data(0x0A);
    tft350_write_8bit_data(0x80);

    tft350_write_index(0xB1);
    tft350_write_8bit_data(0xB0);
    tft350_write_8bit_data(0x11);

    tft350_write_index(0xB4);
    tft350_write_8bit_data(0x02);

    tft350_write_index(0xB6);
    tft350_write_8bit_data(0x02);
    tft350_write_8bit_data(0x42);

    tft350_write_index(0xB7);
    tft350_write_8bit_data(0xc6);

    tft350_write_index(0xBE);
    tft350_write_8bit_data(0x00);
    tft350_write_8bit_data(0x04);

    tft350_write_index(0xE9);
    tft350_write_8bit_data(0x00);

    tft350_write_index(0x36);
    tft350_write_8bit_data((1<<3)|(0<<7)|(1<<6)|(1<<5));

    tft350_write_index(0x3A);
    tft350_write_8bit_data(0x66);

    tft350_write_index(0xE0);
    tft350_write_8bit_data(0x00);
    tft350_write_8bit_data(0x07);
    tft350_write_8bit_data(0x10);
    tft350_write_8bit_data(0x09);
    tft350_write_8bit_data(0x17);
    tft350_write_8bit_data(0x0B);
    tft350_write_8bit_data(0x41);
    tft350_write_8bit_data(0x89);
    tft350_write_8bit_data(0x4B);
    tft350_write_8bit_data(0x0A);
    tft350_write_8bit_data(0x0C);
    tft350_write_8bit_data(0x0E);
    tft350_write_8bit_data(0x18);
    tft350_write_8bit_data(0x1B);
    tft350_write_8bit_data(0x0F);

    tft350_write_index(0XE1);
    tft350_write_8bit_data(0x00);
    tft350_write_8bit_data(0x17);
    tft350_write_8bit_data(0x1A);
    tft350_write_8bit_data(0x04);
    tft350_write_8bit_data(0x0E);
    tft350_write_8bit_data(0x06);
    tft350_write_8bit_data(0x2F);
    tft350_write_8bit_data(0x45);
    tft350_write_8bit_data(0x43);
    tft350_write_8bit_data(0x02);
    tft350_write_8bit_data(0x0A);
    tft350_write_8bit_data(0x09);
    tft350_write_8bit_data(0x32);
    tft350_write_8bit_data(0x36);
    tft350_write_8bit_data(0x0F);

    tft350_write_index(0x11);
    system_delay_ms(120);
    tft350_write_index(0x29);

    tft350_write_index(0x36);
    tft350_write_8bit_data((1<<3)|(0<<7)|(1<<6)|(1<<5));

    TFT350_CS(1);
    tft350_clear_color(WHITE);
}

void tft350_show_char_color (uint16_t x, uint16_t y, const char dat,uint16_t tft350_bgcolor,uint16_t tft350_pencolor)
{
    uint8_t i,j;
    TFT350_CS(0);
            for(i = 0; i < 8; i ++)
            {
                tft350_set_region(x + i, y, x + i, y + 15);
                uint8_t temp_top = ascii_font_8x16[dat - 32][i];
                uint8_t temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; j < 8; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        tft350_write_16bit_data(tft350_pencolor);
                    }
                    else
                    {
                        tft350_write_16bit_data(tft350_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; j < 8; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        tft350_write_16bit_data(tft350_pencolor);
                    }
                    else
                    {   
                        tft350_write_16bit_data(tft350_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
    TFT350_CS(1);
}


void tft350_show_num_color (uint16_t x, uint16_t y, const float dat, uint8_t num, uint8_t pointnum,uint16_t tft350_bgcolor,uint16_t tft350_pencolor)
{
    float dat_temp = dat;
    float offset = 1.0;
    char data_buffer[17];
    for (int i  =0; i<17; i++) data_buffer[i] = 0;
    for (int i  =0; i<num + pointnum + 2; i++) data_buffer[i] = '\0';

    if(num < 10)
    {
        for(; num > 0; num--)
            offset *= 10;
        dat_temp = dat_temp - ((int)dat_temp / (int)offset) * offset;
    }
    func_float_to_str(data_buffer, dat_temp, pointnum);
    tft350_show_string_color(x, y, data_buffer,tft350_bgcolor,tft350_pencolor);
}

void tft350_show_string_color (uint16_t x, uint16_t y, const char dat[],uint16_t tft350_bgcolor,uint16_t tft350_pencolor)
{
    uint8_t j = 0;
    while(dat[j] != '\0')
    {
        tft350_show_char_color(x + 8 * j, y, dat[j],tft350_bgcolor,tft350_pencolor);
        j ++;
    }
}

void tft350_draw_point_color (uint16_t x, uint16_t y, const uint16_t color)
{
    TFT350_CS(0);
    tft350_set_region(x, y, x, y);
    tft350_write_16bit_data(color);
    TFT350_CS(1);
}

void tft350_show_image (uint16_t x, uint16_t y, const uint16_t *image, uint16_t width, uint16_t height)
{

    uint32_t i = 0, j = 0;
    uint16_t color = 0;
    uint32_t width_index = 0, height_index = 0;

    TFT350_CS(0);
    tft350_set_region(x, y, x + width - 1, y + height - 1);

    for(j = 0; j < height; j ++)
    {
        height_index = j;
        for(i = 0; i < width; i ++)
        {
            width_index = i;
            color = *(image + height_index * width + width_index);
            color = ((color & 0xff) << 8) | (color >> 8);
            tft350_write_16bit_data(color);
        }
    }
    TFT350_CS(1);
}