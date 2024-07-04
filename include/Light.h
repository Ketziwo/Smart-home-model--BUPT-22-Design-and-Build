//
// Created by Ma YiRan on 2024/7/3.
//
#ifndef LIGHT_H
#define LIGHT_H

#include <SevenSegmentTM1637.h>
#include <PIN.h>

void initLight();
void displayNum(int);
void displayRGB(int change = 0, int R = 1, int G = 1, int B = 1);

#endif //LIGHT_H
