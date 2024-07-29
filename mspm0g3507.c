/* author : TangSong
 * description : empty
 * date : 2024/7/21
 */
#include "Library/COMMON.h"

int main(void){
    SYSCFG_DL_init();
    tft350_init();
    esp01_init("abcdp","cptbtptp","192.168.118.246","8082");
    tft350_show_string(0, 0, "udp connection ok!");
    esp01_start();
    icm20602_init();
    tft350_show_string(0, 20, "start to transmit data...");
    float yaw = 0.0f;
    float yawRate = 0.0f;
    while (1) {
        system_delay_ms(10);
        icm20602_get_gyro();
        yawRate = icm20602_gyro_z;
        yaw += yawRate * 0.01f;
        esp01_oscilloscope_channel(0, yaw);
        esp01_oscilloscope_channel(1, yawRate);
        elsp01_oscilloscope_send();
        tft350_show_string(0, 40, "yaw:");
        tft350_show_float(50, 40, yaw,3,3);
        tft350_show_string(0, 60, "yawR:");
        tft350_show_float(60, 60, yawRate ,3,3);
    }
}