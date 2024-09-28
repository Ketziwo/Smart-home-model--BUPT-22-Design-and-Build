//
// Created by Ma YiRan on 2024/7/3.
//
#include <Clock.h>

Clock::Clock() {
    display = new SevenSegmentTM1637(CLK_PIN, DIO_PIN);
    display->begin(); // 初始化数码管
    display->setBacklight(100); // 设置数码管亮度为 100%
}

void Clock::print(int num) {
    if(num > 9999) num = 9999;
    else if(num < -999) num = -999;
    display->clear();
    display->print(num); //数码管显示 A0 模拟值
}

void Clock::printTime(int hour, int min) {
    print((hour%24)*100 + (min%60));
    display->setColonOn(true);
}

