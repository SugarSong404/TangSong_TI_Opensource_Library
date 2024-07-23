#ifndef COMMON_H
#define COMMON_H

#include "ti_msp_dl_config.h"

#include "/Basic/TFT180.h"
#include "/Basic/ICM20602.h"
#include "/Basic/OpenMv.h"

#include "/ti/eeprom/emulation_type_b/eeprom_emulation_type_b.h"

#define system_delay_ms(m)    delay_cycles((m*32000))

#endif