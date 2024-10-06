//
// Created by Dai Hao on 2024/7/4.
//

#ifndef PIN_H
#define PIN_H

#include <pins_arduino.h>

// from CardReader.h
const unsigned int RST_PIN = 46; // 读卡器复位
const unsigned int SS_PIN = 53; // 读卡器设置

// from Doorbell.h
const unsigned int BELL_PIN = 45; // 触摸传感器
const unsigned int BEEP_PIN = 44; // 蜂鸣器

// from Flame.h
const unsigned int flamePin = 24; // 火源报警器

// from Humid_Temp.h
const unsigned int DHTPIN = A0; // 温湿度传感器
const unsigned int RAIN_PIN = 23; // 雨滴传感器

// from Infrared.h
const unsigned int RECV_PIN = 2; // 红外传感器

// from Light.h
const unsigned int DIN_R_PIN = 27;
const unsigned int DIN_G_PIN = 28;
const unsigned int DIN_B_PIN = 29;

const unsigned int MBED_R_PIN = 31;
const unsigned int MBED_G_PIN = 32;
const unsigned int MBED_B_PIN = 33;

const unsigned int SBED_R_PIN = 35;
const unsigned int SBED_G_PIN = 36;
const unsigned int SBED_B_PIN = 37;

const unsigned int WASH_R_PIN = 39;
const unsigned int WASH_G_PIN = 40;
const unsigned int WASH_B_PIN = 41;

// from Clock.h
const unsigned int CLK_PIN = 42; // 定义 CLK 引脚
const unsigned int DIO_PIN = 43; // 定义 DIO 引脚
const unsigned int LIGHT_PIN = A4; // 定义光敏器件引脚

// from Motor.h
const unsigned int Door_PIN = 4; // 门舵机引脚
const unsigned int WindowKC_PIN = 5; // 厨房窗户舵机引脚
const unsigned int WindowWS_PIN = 6; // 卫生间窗户舵机引脚
const unsigned int Fan_CTRL = 7; // 风扇轴舵机引脚
const unsigned int Fan_PIN = 3; // 风扇引脚

#endif //PIN_H