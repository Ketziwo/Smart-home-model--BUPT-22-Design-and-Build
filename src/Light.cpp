//
// Created by Ma YiRan on 2024/7/3.
//
#include "Light.h"

SevenSegmentTM1637 display(CLK_PIN, DIO_PIN);

void initLight() {
    display.begin(); // 初始化数码管
    display.setBacklight(100); // 设置数码管亮度为 100%
}
void displayLight(int num) {
    if(num > 9999) num = 9999;
    else if(num < -999) num = -999;
    display.clear();
    display.print(num); //数码管显示 A0 模拟值
}