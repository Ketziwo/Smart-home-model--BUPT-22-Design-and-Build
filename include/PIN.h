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
const unsigned int BELL_PIN = 25; // 触摸传感器
const unsigned int BEEP_PIN = 45; // 蜂鸣器

// from Flame.h
const unsigned int flamePin = 8; // 火源报警器

// from Humid_Temp.h
const unsigned int DHTPIN = A0; // 温湿度传感器
const unsigned int RAIN_PIN = A1; // 雨滴传感器

// from Infrared.h
const unsigned int RECV_PIN = 22; // 红外传感器

// from Light.h
const unsigned int DIN_R_PIN = 5;
const unsigned int DIN_G_PIN = 6;
const unsigned int DIN_B_PIN = 7;

const unsigned int MBED_R_PIN = 35;
const unsigned int MBED_G_PIN = 36;
const unsigned int MBED_B_PIN = 37;

const unsigned int SBED_R_PIN = 35;
const unsigned int SBED_G_PIN = 36;
const unsigned int SBED_B_PIN = 37;

const unsigned int WASH_R_PIN = 35;
const unsigned int WASH_G_PIN = 36;
const unsigned int WASH_B_PIN = 37;

// from Clock.h
const unsigned int CLK_PIN = 43; // 定义 CLK 引脚
const unsigned int DIO_PIN = 44; // 定义 DIO 引脚
const unsigned int LIGHT_PIN = A2; // 定义光敏器件引脚

// from Motor.h
const unsigned int Door_PIN = 2; // 门舵机引脚
const unsigned int WindowKC_PIN = 3; // 厨房窗户舵机引脚
const unsigned int WindowWS_PIN = 4; // 卫生间窗户舵机引脚
const unsigned int Fan_CTRL = 24; // 风扇轴舵机引脚
const unsigned int Fan_PIN = 23; // 风扇引脚

#endif //PIN_H