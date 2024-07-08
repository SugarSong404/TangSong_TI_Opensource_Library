/* author : TangSong
 * description : A example that records the number of times a device is turned on
 * date : 2024/7/9
 */
#include "code/COMMON.h"
#include "code/TFT180.h"
#include "ti/eeprom/emulation_type_b/eeprom_emulation_type_b.h"
const uint32_t EEPROM[4096] __attribute((used)) __attribute((section(".EEPROM")))={0};
int start_times = 0;
int main(void)
{
    SYSCFG_DL_init();
    EEPROM_TypeB_init();
    start_times = EEPROM_TypeB_readDataItem(0x0011);
    EEPROM_TypeB_write(0x0011,start_times+1);
    tft180_init();
    while (1) {
        tft180_show_string(0, 0, "Start Times:");
        tft180_show_int(0, 20, start_times, 3);
        delay_cycles(16000000);
    }
}
