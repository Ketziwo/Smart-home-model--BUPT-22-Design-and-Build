//
// Created by Dai Hao on 2024/9/27.
//
#ifndef CLOCK_H
#define CLOCK_H

#include <SevenSegmentTM1637.h>
#include <PIN.h>

class Clock {
public:
    Clock();
    void print(int num);
    void printTime(int hour, int min);
private:
    SevenSegmentTM1637 *display;
};

#endif