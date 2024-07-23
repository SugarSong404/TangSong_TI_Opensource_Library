#include "ICM20602.h"
int16_t icm20602_gyro_x = 0, icm20602_gyro_y = 0, icm20602_gyro_z = 0;   
int16_t icm20602_acc_x = 0, icm20602_acc_y = 0, icm20602_acc_z = 0;   
float icm20602_transition_factor[2] = {4096, 16.4};   
#define ICM20602_CS(x)              ((x) ? (DL_GPIO_setPins(OTHER_PORT,OTHER_ICM_CS_PIN)) : (DL_GPIO_clearPins(OTHER_PORT,OTHER_ICM_CS_PIN)))

void spi_write_8bit_register(uint8_t reg, uint8_t data){
    DL_SPI_transmitData8(ICM_SPI_INST, reg); 
    while (DL_SPI_isBusy(ICM_SPI_INST));
    DL_SPI_transmitData8(ICM_SPI_INST, data); 
    while (DL_SPI_isBusy(ICM_SPI_INST));
}
void spi_read_8bit_registers(uint8_t reg, uint8_t *data, uint32_t len){
    DL_SPI_transmitData8(ICM_SPI_INST,reg);
    while (DL_SPI_isBusy(ICM_SPI_INST));
    for (int i = 0; i< len; i++) {
        DL_SPI_transmitData8(ICM_SPI_INST,0);
        while (DL_SPI_isBusy(ICM_SPI_INST));
        while (!DL_SPI_isRXFIFOEmpty(ICM_SPI_INST)) 
            data[i] = DL_SPI_receiveData8(ICM_SPI_INST);
    }
}
uint8_t spi_read_8bit_register(uint8_t reg){
    DL_SPI_transmitData8(ICM_SPI_INST,reg);
    while (DL_SPI_isBusy(ICM_SPI_INST));
    DL_SPI_transmitData8(ICM_SPI_INST,0);
    while (DL_SPI_isBusy(ICM_SPI_INST));
    uint8_t data = 0;
    while (!DL_SPI_isRXFIFOEmpty(ICM_SPI_INST)) 
        data = DL_SPI_receiveData8(ICM_SPI_INST);
    return data;
}
static void icm20602_write_register(uint8_t reg, uint8_t data)
{
    ICM20602_CS(0);
    spi_write_8bit_register(reg | ICM20602_SPI_W, data);
    ICM20602_CS(1);
}
static uint8_t icm20602_read_register(uint8_t reg)
{
    uint8_t data = 0;
    ICM20602_CS(0);
    data = spi_read_8bit_register(reg | ICM20602_SPI_R);
    ICM20602_CS(1);
    return data;
}
static void icm20602_read_registers(uint8_t reg, uint8_t *data, uint32_t len)
{
    ICM20602_CS(0);
    spi_read_8bit_registers(reg | ICM20602_SPI_R, data, len);
    ICM20602_CS(1);
}
uint8_t icm20602_self_check (void)
{
    uint8_t dat = 0, return_state = 0;
    uint16_t timeout_count = 0;

    while(0x12 != dat)                                                   
    {
        if(ICM20602_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state =  1;
            break;
        }
        dat = icm20602_read_register(ICM20602_WHO_AM_I);
    }
    return return_state;
}

void icm20602_get_acc (void)
{
    uint8_t dat[6];

    icm20602_read_registers(ICM20602_ACCEL_XOUT_H, dat, 6);
    icm20602_acc_x = (int16_t)(((uint16_t)dat[0] << 8 | dat[1]));
    icm20602_acc_y = (int16_t)(((uint16_t)dat[2] << 8 | dat[3]));
    icm20602_acc_z = (int16_t)(((uint16_t)dat[4] << 8 | dat[5]));
}

void icm20602_get_gyro (void)
{
    uint8_t dat[6];

    icm20602_read_registers(ICM20602_GYRO_XOUT_H, dat, 6);
    icm20602_gyro_x = (int16_t)(((uint16_t)dat[0] << 8 | dat[1]));
    icm20602_gyro_y = (int16_t)(((uint16_t)dat[2] << 8 | dat[3]));
    icm20602_gyro_z = (int16_t)(((uint16_t)dat[4] << 8 | dat[5]));
}

uint8_t icm20602_init (void)
{
    uint8_t val = 0x0, return_state = 0;
    uint16_t timeout_count = 0;

    system_delay_ms(10);  

    do
    {
        if(icm20602_self_check())
        {
            return_state = 1;
            break;
        }
        icm20602_write_register(ICM20602_PWR_MGMT_1, 0x80);                     // 复位设备
        system_delay_ms(2);

        do
        {                                                                       // 等待复位成功
            val = icm20602_read_register(ICM20602_PWR_MGMT_1);
            if(ICM20602_TIMEOUT_COUNT < timeout_count ++)
            {
                return_state = 2;
                break;
            }
        }while(0x41 != val);
        if(2 == return_state)
        {
            break;
        }

        icm20602_write_register(ICM20602_PWR_MGMT_1,     0x01);             
        icm20602_write_register(ICM20602_PWR_MGMT_2,     0x00);        
        icm20602_write_register(ICM20602_CONFIG,         0x01);                 
        icm20602_write_register(ICM20602_SMPLRT_DIV,     0x07);      

        icm20602_write_register(ICM20602_ACCEL_CONFIG, 0x10);
        icm20602_transition_factor[0] = 4096;


        icm20602_write_register(ICM20602_GYRO_CONFIG, 0x18);
        icm20602_transition_factor[1] = 16.4;

        icm20602_write_register(ICM20602_ACCEL_CONFIG_2, 0x03); 
    }while(0);
    return return_state;
}

