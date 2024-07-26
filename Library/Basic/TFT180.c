#include "TFT180.h"
#define TFT180_DC(x)                   ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_DC_PIN))  : (DL_GPIO_clearPins(TFT_PORT, TFT_DC_PIN)))
#define TFT180_RST(x)                  ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_RES_PIN)) : (DL_GPIO_clearPins(TFT_PORT, TFT_RES_PIN)))
#define TFT180_CS(x)                   ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_CS_PIN))  : (DL_GPIO_clearPins(TFT_PORT, TFT_CS_PIN)))
#define TFT180_BL(x)                   ((x) ? (DL_GPIO_setPins(TFT_PORT, TFT_BL_PIN))  : (DL_GPIO_clearPins(TFT_PORT, TFT_BL_PIN)))

void tft180_write_8bit_data (uint8_t data){
    DL_SPI_transmitData8  (TFT_SPI_INST, data);while (DL_SPI_isBusy(TFT_SPI_INST));
}
void tft180_write_16bit_data (uint16_t data){
    DL_SPI_transmitData8(TFT_SPI_INST, (uint8_t)((data & 0xFF00) >> 8));while (DL_SPI_isBusy(TFT_SPI_INST));
    DL_SPI_transmitData8(TFT_SPI_INST, (uint8_t)(data & 0x00FF));while (DL_SPI_isBusy(TFT_SPI_INST));
}
static void tft180_write_index (uint8_t dat)
{
    TFT180_DC(0);
    tft180_write_8bit_data(dat);
    TFT180_DC(1);
}
static void tft180_set_region (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    tft180_write_index(0x2a);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(x1 + 1);
    tft180_write_8bit_data(0x0);
    tft180_write_8bit_data(x2 + 1);

    tft180_write_index(0x2b);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(y1 + 2);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(y2 + 2);
    tft180_write_index(0x2c);
}
void tft180_clear_color (uint16_t tft180_bgcolor)
{
    uint16_t i = tft180_x_max * tft180_y_max;

    TFT180_CS(0);
    tft180_set_region(0, 0, tft180_x_max - 1, tft180_y_max - 1);
    for( ; i!= 0; i --)
    {
        tft180_write_16bit_data(tft180_bgcolor);
    }
    TFT180_CS(1);
}
void tft180_init (void)
{
    TFT180_RST(0);
    system_delay_ms(10);
    TFT180_RST(1);
    system_delay_ms(120);
    TFT180_CS(0);

    tft180_write_index(0x11);
    system_delay_ms(120);

    tft180_write_index(0xB1);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);

    tft180_write_index(0xB2);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);

    tft180_write_index(0xB3);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);
    tft180_write_8bit_data(0x01);
    tft180_write_8bit_data(0x2C);
    tft180_write_8bit_data(0x2D);

    tft180_write_index(0xB4);
    tft180_write_8bit_data(0x07);

    tft180_write_index(0xC0);
    tft180_write_8bit_data(0xA2);
    tft180_write_8bit_data(0x02);
    tft180_write_8bit_data(0x84);
    tft180_write_index(0xC1);
    tft180_write_8bit_data(0xC5);

    tft180_write_index(0xC2);
    tft180_write_8bit_data(0x0A);
    tft180_write_8bit_data(0x00);

    tft180_write_index(0xC3);
    tft180_write_8bit_data(0x8A);
    tft180_write_8bit_data(0x2A);
    tft180_write_index(0xC4);
    tft180_write_8bit_data(0x8A);
    tft180_write_8bit_data(0xEE);

    tft180_write_index(0xC5);
    tft180_write_8bit_data(0x0E);

    tft180_write_index(0x36);

    tft180_write_8bit_data(1<<7 | 0<<6 | 1<<5); 


    tft180_write_index(0xe0);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x1a);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x18);
    tft180_write_8bit_data(0x2f);
    tft180_write_8bit_data(0x28);
    tft180_write_8bit_data(0x20);
    tft180_write_8bit_data(0x22);
    tft180_write_8bit_data(0x1f);
    tft180_write_8bit_data(0x1b);
    tft180_write_8bit_data(0x23);
    tft180_write_8bit_data(0x37);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x07);
    tft180_write_8bit_data(0x02);
    tft180_write_8bit_data(0x10);

    tft180_write_index(0xe1);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x1b);
    tft180_write_8bit_data(0x0f);
    tft180_write_8bit_data(0x17);
    tft180_write_8bit_data(0x33);
    tft180_write_8bit_data(0x2c);
    tft180_write_8bit_data(0x29);
    tft180_write_8bit_data(0x2e);
    tft180_write_8bit_data(0x30);
    tft180_write_8bit_data(0x30);
    tft180_write_8bit_data(0x39);
    tft180_write_8bit_data(0x3f);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x07);
    tft180_write_8bit_data(0x03);
    tft180_write_8bit_data(0x10);

    tft180_write_index(0x2a);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x00 + 2);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x80 + 2);

    tft180_write_index(0x2b);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x00 + 3);
    tft180_write_8bit_data(0x00);
    tft180_write_8bit_data(0x80 + 3);

    tft180_write_index(0xF0);
    tft180_write_8bit_data(0x01);
    tft180_write_index(0xF6);
    tft180_write_8bit_data(0x00);

    tft180_write_index(0x3A);
    tft180_write_8bit_data(0x05);
    tft180_write_index(0x29);
    TFT180_CS(1);

    tft180_clear_color(tft180_bgcolor);
}

void tft180_show_char_color (uint8_t x, uint8_t y, const char dat,uint16_t tft180_bgcolor,uint16_t tft180_pencolor)
{
    uint8_t i,j;
    TFT180_CS(0);
            for(i = 0; i < 8; i ++)
            {
                tft180_set_region(x + i, y, x + i, y + 15);
                uint8_t temp_top = ascii_font_8x16[dat - 32][i];
                uint8_t temp_bottom = ascii_font_8x16[dat - 32][i + 8];
                for(j = 0; j < 8; j ++)
                {
                    if(temp_top & 0x01)
                    {
                        tft180_write_16bit_data(tft180_pencolor);
                    }
                    else
                    {
                        tft180_write_16bit_data(tft180_bgcolor);
                    }
                    temp_top >>= 1;
                }
                for(j = 0; j < 8; j ++)
                {
                    if(temp_bottom & 0x01)
                    {
                        tft180_write_16bit_data(tft180_pencolor);
                    }
                    else
                    {   
                        tft180_write_16bit_data(tft180_bgcolor);
                    }
                    temp_bottom >>= 1;
                }
            }
    TFT180_CS(1);
}

void tft180_show_num_color (uint8_t x, uint8_t y, const float dat, uint8_t num, uint8_t pointnum,uint16_t tft180_bgcolor,uint16_t tft180_pencolor)
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
    tft180_show_string_color(x, y, data_buffer,tft180_bgcolor,tft180_pencolor);
}

void tft180_show_string_color (uint8_t x, uint8_t y, const char dat[],uint16_t tft180_bgcolor,uint16_t tft180_pencolor)
{
    uint8_t j = 0;
    while(dat[j] != '\0')
    {
        tft180_show_char_color(x + 8 * j, y, dat[j],tft180_bgcolor,tft180_pencolor);
        j ++;
    }
}