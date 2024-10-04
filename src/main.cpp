#include <Arduino.h>

/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5Core sample source code
*                          配套  M5Core 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/pahub
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/unit/pahub
*
* Describe: PaHUB.
* Date: 2021/8/31
*******************************************************************************
  Please connect to Port A, Use PaHUB Unit to expand multiple I2C devices and
scan the I2C addresses of the slave devices in order. 请连接端口A, 使用PaHUB
Unit扩展多个I2C设备，并依次扫描从设备的I2C地址。
*/

#include "M5AtomS3.h"

#include "ClosedCube_TCA9548A.h"

#define FRONT 2

#define X_LOCAL  100
#define Y_LOCAL  35
#define X_OFFSET 160
#define Y_OFFSET 15

#define PaHub_I2C_ADDRESS 0x70

ClosedCube::Wired::TCA9548A tca9548a;

void setup() {
    Wire.begin(2,1);
    auto cfg = M5.config();
    AtomS3.begin(cfg);

    tca9548a.address(PaHub_I2C_ADDRESS);  // Set the I2C address.
    AtomS3.Display.setTextColor(GREEN);
    AtomS3.Display.setTextSize(2);
    AtomS3.Display.drawString("PaHUB Example", AtomS3.Display.width() / 2, AtomS3.Display.height() / 2);

}

void loop() {
    uint8_t returnCode = 0;
    uint8_t address;
    for (uint8_t channel = 0; channel < TCA9548A_MAX_CHANNELS; channel++) {
        
        AtomS3.Display.clear();
        AtomS3.Display.drawString("C: ", 5, 5);
        AtomS3.Display.drawString(String(channel), 40, 5 + Y_OFFSET * channel);

        returnCode = tca9548a.selectChannel(channel);
        if (returnCode == 0) {
            for (address = 0x01; address < 0x7F; address++) {
                Wire.beginTransmission(address);
                returnCode = Wire.endTransmission();
                if (returnCode == 0) {
                    if (address != 112) {
                    AtomS3.Display.drawString(String(address), 75, 5 + Y_OFFSET * channel);
                    }
                }
            }
        }
        delay(1000);
    }
}
