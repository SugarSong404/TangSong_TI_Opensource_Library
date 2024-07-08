#include "code/COMMON.h"
#include "ti/eeprom/emulation_type_b/eeprom_emulation_type_b.h"

const uint32_t EEPROM[4096] __attribute((used)) __attribute((section(".EEPROM")))={0};
int main(void)
{
    SYSCFG_DL_init();
    tft180_init();
    EEPROM_TypeB_init();
    while (1) {
        tft180_show_string(0, 0, "Hello,world!");
        delay_cycles(16000000);
    }
}
