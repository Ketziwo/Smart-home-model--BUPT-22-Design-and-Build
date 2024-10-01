//
// Created by Dai Hao on 2024/9/29.
//
#ifndef TIMER_H
#define TIMER_H

struct cycle{
    int doorOpenTime = 0;
    int fanAngle = -1;
    int DinLight = -1;
    int MBLight = -1;
    int SBLight = -1;
    int WSLight = -1;
};

// 计时器函数
void cycling();


#endif