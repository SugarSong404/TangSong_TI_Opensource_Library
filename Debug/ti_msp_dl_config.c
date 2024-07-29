/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_SPI_backupConfig gICM_SPIBackup;
DL_SPI_backupConfig gTFT_SPIBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_ESP01_init();
    SYSCFG_DL_OPENMV_init();
    SYSCFG_DL_ICM_SPI_init();
    SYSCFG_DL_TFT_SPI_init();
    /* Ensure backup structures have no valid state */

	gICM_SPIBackup.backupRdy 	= false;
	gTFT_SPIBackup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_SPI_saveConfiguration(ICM_SPI_INST, &gICM_SPIBackup);
	retStatus &= DL_SPI_saveConfiguration(TFT_SPI_INST, &gTFT_SPIBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_SPI_restoreConfiguration(ICM_SPI_INST, &gICM_SPIBackup);
	retStatus &= DL_SPI_restoreConfiguration(TFT_SPI_INST, &gTFT_SPIBackup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_UART_Main_reset(ESP01_INST);
    DL_UART_Main_reset(OPENMV_INST);
    DL_SPI_reset(ICM_SPI_INST);
    DL_SPI_reset(TFT_SPI_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_UART_Main_enablePower(ESP01_INST);
    DL_UART_Main_enablePower(OPENMV_INST);
    DL_SPI_enablePower(ICM_SPI_INST);
    DL_SPI_enablePower(TFT_SPI_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_ESP01_IOMUX_TX, GPIO_ESP01_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_ESP01_IOMUX_RX, GPIO_ESP01_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_OPENMV_IOMUX_TX, GPIO_OPENMV_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_OPENMV_IOMUX_RX, GPIO_OPENMV_IOMUX_RX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_ICM_SPI_IOMUX_SCLK, GPIO_ICM_SPI_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_ICM_SPI_IOMUX_PICO, GPIO_ICM_SPI_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_ICM_SPI_IOMUX_POCI, GPIO_ICM_SPI_IOMUX_POCI_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_ICM_SPI_IOMUX_CS1, GPIO_ICM_SPI_IOMUX_CS1_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_TFT_SPI_IOMUX_SCLK, GPIO_TFT_SPI_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_TFT_SPI_IOMUX_PICO, GPIO_TFT_SPI_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_TFT_SPI_IOMUX_POCI, GPIO_TFT_SPI_IOMUX_POCI_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_TFT_SPI_IOMUX_CS0, GPIO_TFT_SPI_IOMUX_CS0_FUNC);

    DL_GPIO_initDigitalOutput(TFT_DC_IOMUX);

    DL_GPIO_initDigitalOutput(TFT_RES_IOMUX);

    DL_GPIO_initDigitalOutput(TFT_CS_IOMUX);

    DL_GPIO_initDigitalOutput(TFT_BL_IOMUX);

    DL_GPIO_initDigitalOutput(OTHER_ICM_CS_IOMUX);

    DL_GPIO_initDigitalOutput(OTHER_ESP_EN_IOMUX);

    DL_GPIO_initDigitalOutput(OTHER_ESP_RST_IOMUX);

    DL_GPIO_clearPins(GPIOB, TFT_DC_PIN |
		TFT_RES_PIN |
		OTHER_ESP_RST_PIN);
    DL_GPIO_setPins(GPIOB, TFT_CS_PIN |
		TFT_BL_PIN |
		OTHER_ICM_CS_PIN |
		OTHER_ESP_EN_PIN);
    DL_GPIO_enableOutput(GPIOB, TFT_DC_PIN |
		TFT_RES_PIN |
		TFT_CS_PIN |
		TFT_BL_PIN |
		OTHER_ICM_CS_PIN |
		OTHER_ESP_EN_PIN |
		OTHER_ESP_RST_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();

}



static const DL_UART_Main_ClockConfig gESP01ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gESP01Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_ESP01_init(void)
{
    DL_UART_Main_setClockConfig(ESP01_INST, (DL_UART_Main_ClockConfig *) &gESP01ClockConfig);

    DL_UART_Main_init(ESP01_INST, (DL_UART_Main_Config *) &gESP01Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(ESP01_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(ESP01_INST, ESP01_IBRD_32_MHZ_115200_BAUD, ESP01_FBRD_32_MHZ_115200_BAUD);



    DL_UART_Main_enable(ESP01_INST);
}

static const DL_UART_Main_ClockConfig gOPENMVClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gOPENMVConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_OPENMV_init(void)
{
    DL_UART_Main_setClockConfig(OPENMV_INST, (DL_UART_Main_ClockConfig *) &gOPENMVClockConfig);

    DL_UART_Main_init(OPENMV_INST, (DL_UART_Main_Config *) &gOPENMVConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(OPENMV_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(OPENMV_INST, OPENMV_IBRD_32_MHZ_115200_BAUD, OPENMV_FBRD_32_MHZ_115200_BAUD);



    DL_UART_Main_enable(OPENMV_INST);
}

static const DL_SPI_Config gICM_SPI_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO4_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
    .chipSelectPin = DL_SPI_CHIP_SELECT_1,
};

static const DL_SPI_ClockConfig gICM_SPI_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_ICM_SPI_init(void) {
    DL_SPI_setClockConfig(ICM_SPI_INST, (DL_SPI_ClockConfig *) &gICM_SPI_clockConfig);

    DL_SPI_init(ICM_SPI_INST, (DL_SPI_Config *) &gICM_SPI_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     8000000 = (32000000)/((1 + 1) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(ICM_SPI_INST, 1);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(ICM_SPI_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(ICM_SPI_INST);
}
static const DL_SPI_Config gTFT_SPI_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO4_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
    .chipSelectPin = DL_SPI_CHIP_SELECT_0,
};

static const DL_SPI_ClockConfig gTFT_SPI_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_TFT_SPI_init(void) {
    DL_SPI_setClockConfig(TFT_SPI_INST, (DL_SPI_ClockConfig *) &gTFT_SPI_clockConfig);

    DL_SPI_init(TFT_SPI_INST, (DL_SPI_Config *) &gTFT_SPI_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     8000000 = (32000000)/((1 + 1) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(TFT_SPI_INST, 1);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(TFT_SPI_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(TFT_SPI_INST);
}

