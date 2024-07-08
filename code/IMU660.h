#ifndef IMU660_H
#define IMU660_H
#include "COMMON.h"
#define IMU660RA_DEV_ADDR             (0x69)                                    // SA0接地：0x68 SA0上拉：0x69 模块默认上拉
#define IMU_SPI_W                (0x00)
#define IMU_SPI_R                (0x80)

#define IMU660RA_CHIP_ID              (0x00)
#define IMU660RA_PWR_CONF             (0x7C)
#define IMU660RA_PWR_CTRL             (0x7D)
#define IMU660RA_INIT_CTRL            (0x59)
#define IMU660RA_INIT_DATA            (0x5E)
#define IMU660RA_INT_STA              (0x21)
#define IMU660RA_ACC_ADDRESS          (0x0C)
#define IMU660RA_GYRO_ADDRESS         (0x12)
#define IMU660RA_ACC_CONF             (0x40)
#define IMU660RA_ACC_RANGE            (0x41)
#define IMU660RA_GYR_CONF             (0x42)
#define IMU660RA_GYR_RANGE            (0x43)
#define IMU660RA_ACC_SAMPLE           (0x02)        
#define IMU660RA_TIMEOUT_COUNT        (0x00FF)      

uint8_t imu660ra_init (void);
uint8_t imu660ra_self_check (void);
void imu660ra_get_acc (void);
void imu660ra_get_gyro (void);

extern int16_t imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;                 // 三轴陀螺仪数据      GYRO (陀螺仪)
extern int16_t imu660ra_acc_x, imu660ra_acc_y, imu660ra_acc_z;                    // 三轴加速度计数据     ACC  (accelerometer 加速度计)
#endif