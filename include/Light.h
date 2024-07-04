//
// Created by Ma YiRan on 2024/7/3.
//
#ifndef LIGHT_H
#define LIGHT_H

#include <SevenSegmentTM1637.h>

const unsigned int CLK_PIN = 7; // 定义 CLK 引脚
const unsigned int DIO_PIN = 8; // 定义 DIO 引脚
const unsigned int LIGHT_PIN = A2; // 定义光敏器件引脚

void initLight();
void displayLight(int);

#endif //LIGHT_H
