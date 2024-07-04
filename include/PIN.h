//
// Created by Dai Hao on 2024/7/4.
//

#ifndef PIN_H
#define PIN_H

#include <pins_arduino.h>

// from CardReader.h
const unsigned int RST_PIN = 5; // 读卡器复位
const unsigned int SS_PIN = 53; // 读卡器设置

// from Doorbell.h
const unsigned int BELL_PIN = 4; // 触摸传感器
const unsigned int BEEP_PIN = 12; // 蜂鸣器

// from Flame.h
const unsigned int flamePin = 8; // 烟雾报警器

// from Humid_Temp.h
const unsigned int DHTPIN = A0; // 温湿度传感器
const unsigned int RAIN_PIN = A1; // 雨滴传感器

// from Infrared.h
const unsigned int RECV_PIN = 11; // 红外传感器

// from Light.h
const unsigned int G_PIN = A8;
const unsigned int R_PIN = A10;
const unsigned int B_PIN = A9;

const unsigned int CLK_PIN = 7; // 定义 CLK 引脚
const unsigned int DIO_PIN = 6; // 定义 DIO 引脚
const unsigned int LIGHT_PIN = A2; // 定义光敏器件引脚

// from Motor.h
const unsigned int Door_Pin = 2; // 旋转门舵机引脚
const unsigned int Window_Pin = 3; // 窗户舵机引脚
const unsigned int Fan_Pin = 13; // 风扇引脚

#endif //PIN_H
