/* author : TangSong
 * description : Will get data from openmv and show it.A example for using openmv.h
 * date : 2024/7/21
 */
#include "Library/COMMON.h"
uint8_t openmv_func_tftchar(uint8_t* data){
    static uint8_t num = 0;
    uint8_t ptr = 0;
    num++;
    tft180_show_int(0, 20, OMI(data,ptr),3);
    tft180_show_string(0, 40, OMS(data, ptr));
    tft180_show_float(0, 60, OMF(data,ptr),3,3);
    tft180_show_int(0, 80, OMB(data,ptr),3);
    if(num==50){
        num = 0;
        return 0;
    }
    else return 1;
} 
int main(void)
{
    SYSCFG_DL_init();
    tft180_init();
    tft180_show_int(0, 0, openmv_init(),3);
    openmv_cmd(0xe0, openmv_func_tftchar);
    while (1) {
        system_delay_ms(500);
    }
}