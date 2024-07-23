/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for OPENMV */
#define OPENMV_INST                                                        UART0
#define OPENMV_INST_IRQHandler                                  UART0_IRQHandler
#define OPENMV_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_OPENMV_RX_PORT                                                GPIOB
#define GPIO_OPENMV_TX_PORT                                                GPIOB
#define GPIO_OPENMV_RX_PIN                                         DL_GPIO_PIN_1
#define GPIO_OPENMV_TX_PIN                                         DL_GPIO_PIN_0
#define GPIO_OPENMV_IOMUX_RX                                     (IOMUX_PINCM13)
#define GPIO_OPENMV_IOMUX_TX                                     (IOMUX_PINCM12)
#define GPIO_OPENMV_IOMUX_RX_FUNC                      IOMUX_PINCM13_PF_UART0_RX
#define GPIO_OPENMV_IOMUX_TX_FUNC                      IOMUX_PINCM12_PF_UART0_TX
#define OPENMV_BAUD_RATE                                                 (19200)
#define OPENMV_IBRD_32_MHZ_19200_BAUD                                      (104)
#define OPENMV_FBRD_32_MHZ_19200_BAUD                                       (11)




/* Defines for ICM_SPI */
#define ICM_SPI_INST                                                       SPI1
#define ICM_SPI_INST_IRQHandler                                 SPI1_IRQHandler
#define ICM_SPI_INST_INT_IRQN                                     SPI1_INT_IRQn
#define GPIO_ICM_SPI_PICO_PORT                                            GPIOB
#define GPIO_ICM_SPI_PICO_PIN                                     DL_GPIO_PIN_8
#define GPIO_ICM_SPI_IOMUX_PICO                                 (IOMUX_PINCM25)
#define GPIO_ICM_SPI_IOMUX_PICO_FUNC                 IOMUX_PINCM25_PF_SPI1_PICO
#define GPIO_ICM_SPI_POCI_PORT                                            GPIOB
#define GPIO_ICM_SPI_POCI_PIN                                     DL_GPIO_PIN_7
#define GPIO_ICM_SPI_IOMUX_POCI                                 (IOMUX_PINCM24)
#define GPIO_ICM_SPI_IOMUX_POCI_FUNC                 IOMUX_PINCM24_PF_SPI1_POCI
/* GPIO configuration for ICM_SPI */
#define GPIO_ICM_SPI_SCLK_PORT                                            GPIOB
#define GPIO_ICM_SPI_SCLK_PIN                                     DL_GPIO_PIN_9
#define GPIO_ICM_SPI_IOMUX_SCLK                                 (IOMUX_PINCM26)
#define GPIO_ICM_SPI_IOMUX_SCLK_FUNC                 IOMUX_PINCM26_PF_SPI1_SCLK
#define GPIO_ICM_SPI_CS1_PORT                                             GPIOA
#define GPIO_ICM_SPI_CS1_PIN                                     DL_GPIO_PIN_27
#define GPIO_ICM_SPI_IOMUX_CS1                                  (IOMUX_PINCM60)
#define GPIO_ICM_SPI_IOMUX_CS1_FUNC             IOMUX_PINCM60_PF_SPI1_CS1_POCI1
/* Defines for TFT_SPI */
#define TFT_SPI_INST                                                       SPI0
#define TFT_SPI_INST_IRQHandler                                 SPI0_IRQHandler
#define TFT_SPI_INST_INT_IRQN                                     SPI0_INT_IRQn
#define GPIO_TFT_SPI_PICO_PORT                                            GPIOB
#define GPIO_TFT_SPI_PICO_PIN                                    DL_GPIO_PIN_17
#define GPIO_TFT_SPI_IOMUX_PICO                                 (IOMUX_PINCM43)
#define GPIO_TFT_SPI_IOMUX_PICO_FUNC                 IOMUX_PINCM43_PF_SPI0_PICO
#define GPIO_TFT_SPI_POCI_PORT                                            GPIOA
#define GPIO_TFT_SPI_POCI_PIN                                    DL_GPIO_PIN_10
#define GPIO_TFT_SPI_IOMUX_POCI                                 (IOMUX_PINCM21)
#define GPIO_TFT_SPI_IOMUX_POCI_FUNC                 IOMUX_PINCM21_PF_SPI0_POCI
/* GPIO configuration for TFT_SPI */
#define GPIO_TFT_SPI_SCLK_PORT                                            GPIOA
#define GPIO_TFT_SPI_SCLK_PIN                                    DL_GPIO_PIN_12
#define GPIO_TFT_SPI_IOMUX_SCLK                                 (IOMUX_PINCM34)
#define GPIO_TFT_SPI_IOMUX_SCLK_FUNC                 IOMUX_PINCM34_PF_SPI0_SCLK
#define GPIO_TFT_SPI_CS0_PORT                                             GPIOA
#define GPIO_TFT_SPI_CS0_PIN                                      DL_GPIO_PIN_2
#define GPIO_TFT_SPI_IOMUX_CS0                                   (IOMUX_PINCM7)
#define GPIO_TFT_SPI_IOMUX_CS0_FUNC                    IOMUX_PINCM7_PF_SPI0_CS0



/* Port definition for Pin Group OTHER */
#define OTHER_PORT                                                       (GPIOB)

/* Defines for ICM_CS: GPIOB.3 with pinCMx 16 on package pin 51 */
#define OTHER_ICM_CS_PIN                                         (DL_GPIO_PIN_3)
#define OTHER_ICM_CS_IOMUX                                       (IOMUX_PINCM16)
/* Port definition for Pin Group TFT */
#define TFT_PORT                                                         (GPIOB)

/* Defines for DC: GPIOB.13 with pinCMx 30 on package pin 1 */
#define TFT_DC_PIN                                              (DL_GPIO_PIN_13)
#define TFT_DC_IOMUX                                             (IOMUX_PINCM30)
/* Defines for RES: GPIOB.18 with pinCMx 44 on package pin 15 */
#define TFT_RES_PIN                                             (DL_GPIO_PIN_18)
#define TFT_RES_IOMUX                                            (IOMUX_PINCM44)
/* Defines for CS: GPIOB.16 with pinCMx 33 on package pin 4 */
#define TFT_CS_PIN                                              (DL_GPIO_PIN_16)
#define TFT_CS_IOMUX                                             (IOMUX_PINCM33)
/* Defines for BL: GPIOB.19 with pinCMx 45 on package pin 16 */
#define TFT_BL_PIN                                              (DL_GPIO_PIN_19)
#define TFT_BL_IOMUX                                             (IOMUX_PINCM45)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_OPENMV_init(void);
void SYSCFG_DL_ICM_SPI_init(void);
void SYSCFG_DL_TFT_SPI_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
