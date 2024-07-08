#include "IMU660.h"

const unsigned char imu660ra_config_file[8195];
int16_t imu660ra_gyro_x = 0, imu660ra_gyro_y = 0, imu660ra_gyro_z = 0;            // 三轴陀螺仪数据      GYRO (陀螺仪)
int16_t imu660ra_acc_x = 0, imu660ra_acc_y = 0, imu660ra_acc_z = 0;               // 三轴加速度计数据     ACC  (accelerometer 加速度计)
float imu660ra_transition_factor[2] = {4096, 16.4};                             // 转换实际值的比例   
#define IMU660RA_CS(x)              ((x) ? (DL_GPIO_setPins(OTHER_PORT,OTHER_IMU_CS_PIN)) : (DL_GPIO_clearPins(OTHER_PORT,OTHER_IMU_CS_PIN)))

void spi_write_8bit_register(uint8_t reg, uint8_t data){
    DL_SPI_transmitData8(IMU_SPI_INST, reg); 
    while (DL_SPI_isBusy(IMU_SPI_INST));
    DL_SPI_transmitData8(IMU_SPI_INST, data); 
    while (DL_SPI_isBusy(IMU_SPI_INST));
}
void spi_write_8bit_registers(uint8_t reg, const uint8_t *data, uint32_t len){
    DL_SPI_transmitData8(IMU_SPI_INST, reg);    
    while (DL_SPI_isBusy(IMU_SPI_INST));     
    for (uint32_t i = 0; i < len; ++i) {
        DL_SPI_transmitData8(IMU_SPI_INST, data[i]); 
        while (DL_SPI_isBusy(IMU_SPI_INST));
    }
}
void spi_read_8bit_registers(uint8_t reg, uint8_t *data, uint32_t len){
    DL_SPI_transmitData8(IMU_SPI_INST,reg);
    while (DL_SPI_isBusy(IMU_SPI_INST));
    for (int i = 0; i< len; i++) {
        DL_SPI_transmitData8(IMU_SPI_INST,0);
        while (DL_SPI_isBusy(IMU_SPI_INST));
        data[i] = DL_SPI_receiveData8(IMU_SPI_INST);
    }
}
static void imu660ra_write_register(uint8_t reg, uint8_t data)
{
    IMU660RA_CS(0);
    spi_write_8bit_register( reg | IMU_SPI_W, data);
    IMU660RA_CS(1);
}
static void imu660ra_write_registers(uint8_t reg, const uint8_t *data, uint32_t len)
{
    IMU660RA_CS(0);
    spi_write_8bit_registers( reg | IMU_SPI_W, data, len);
    IMU660RA_CS(1);
}
static uint8_t imu660ra_read_register(uint8_t reg)
{
    uint8_t data[2];
    IMU660RA_CS(0);
    spi_read_8bit_registers( reg | IMU_SPI_R, data, 2);
    IMU660RA_CS(1);
    return data[1];
}
static void imu660ra_read_registers(uint8_t reg, uint8_t *data, uint32_t len)
{
    uint8_t temp_data[8];
    IMU660RA_CS(0);
    spi_read_8bit_registers( reg | IMU_SPI_R, temp_data, len + 1);
    IMU660RA_CS(1);
    for(int i = 0; i < len; i ++)
    {
        *(data ++) = temp_data[i + 1];
    }
}
uint8_t imu660ra_self_check (void)
{
    uint8_t dat = 0, return_state = 0;
    uint16_t timeout_count = 0;
    do
    {
        if(IMU660RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state =  1;
            break;
        }
        dat = imu660ra_read_register(IMU660RA_CHIP_ID);
        system_delay_ms(1);
    }while(0x24!= dat);                                                    // 读取设备ID是否等于0X24，如果不是0X24则认为没检测到设备
    return return_state;
}
uint8_t imu660ra_init (void)
{
    uint8_t return_state = 0;
    system_delay_ms(20);                                                    // 等待设备上电成功
    imu660ra_read_register(IMU660RA_CHIP_ID);                                                                                   // 读取一下设备ID，将设备设置为SPI模式
    do{
        if(imu660ra_self_check())                                           // IMU660RA自检
        {
            return_state = 1;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CONF, 0x00);                   // 关闭高级省电模式
        system_delay_ms(1);
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x00);                  // 开始对模块进行初始化配置
        imu660ra_write_registers(IMU660RA_INIT_DATA, imu660ra_config_file, sizeof(imu660ra_config_file));                   // 输出配置文件
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x01);                  // 初始化配置结束
        system_delay_ms(20);
        if(1 != imu660ra_read_register(IMU660RA_INT_STA))                       // 检查是否配置完成
        {
            return_state = 2;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CTRL, 0x0E);                       // 开启性能模式  使能陀螺仪、加速度、温度传感器
        imu660ra_write_register(IMU660RA_ACC_CONF, 0xA7);                       // 加速度采集配置 性能模式 正常采集 50Hz  采样频率
        imu660ra_write_register(IMU660RA_GYR_CONF, 0xA9);                       // 陀螺仪采集配置 性能模式 正常采集 200Hz 采样频率

        imu660ra_write_register(IMU660RA_ACC_RANGE, 0x02);
        imu660ra_transition_factor[0] = 4096;

        imu660ra_write_register(IMU660RA_GYR_RANGE, 0x00);
        imu660ra_transition_factor[1] = 16.4;

    }while(0);
    return return_state;
}
void imu660ra_get_acc (void)
{
    uint8_t dat[6];

    imu660ra_read_registers(IMU660RA_ACC_ADDRESS, dat, 6);
    imu660ra_acc_x = (int16_t)(((uint16_t)dat[1]<<8 | dat[0]));
    imu660ra_acc_y = (int16_t)(((uint16_t)dat[3]<<8 | dat[2]));
    imu660ra_acc_z = (int16_t)(((uint16_t)dat[5]<<8 | dat[4]));
}
void imu660ra_get_gyro (void)
{
    uint8_t dat[6];

    imu660ra_read_registers(IMU660RA_GYRO_ADDRESS, dat, 6);
    imu660ra_gyro_x = (int16_t)(((uint16_t)dat[1]<<8 | dat[0]));
    imu660ra_gyro_y = (int16_t)(((uint16_t)dat[3]<<8 | dat[2]));
    imu660ra_gyro_z = (int16_t)(((uint16_t)dat[5]<<8 | dat[4]));
}
