//
// Created by Zhang ZhuHan on 2024/7/3.
//
#include "Flame.h"

#include <Arduino.h>



void flameInit() {
    // 设置输入和输出引脚
    pinMode(flamePin, INPUT);
}

int getFlame() {
    // 读取火焰传感器的值
    return !digitalRead(flamePin);
}