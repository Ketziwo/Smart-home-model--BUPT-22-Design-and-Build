//
// Created by Dai Hao on 2024/7/2.
//

#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>
int command(String command);
void notifyMSG(char* BTNotifyMessage);

// 门控制函数，默认开门5秒, -1开门时间无限，可以调整开门时间
void cmdDoor(bool x, int time = 5);// door on/off

// 窗控制函数，默认0全开/关，1为厨房窗，2为卫生间窗
void cmdWindow(bool x, int id = 0);// window on 2

// 风扇控制函数，默认0扫风，1为直吹客厅，2为直吹主卧，3为直吹次卧
void cmdFan(bool x, int id = 0);// fan on/off 0-3

// 灯光控制函数，默认id0全部房间，1为客厅灯，2为主卧灯，3为次卧灯，4为卫生间灯
void cmdRGB(int x, int id = 0);// light on/off/spark 0-4

// 时间传输函数
void cmdTime(int hh, int min);//time 12 34

// 睡前模式 风扇直吹主卧， 灯光主卧外灯光关闭
void cmdBeforeBed();

// 睡眠模式 所有灯光关闭，风扇直吹主卧
void cmdSleeping();

// 离家模式 Is_home = false，门打开5秒，窗户、灯、风扇关闭
void cmdLeaving();

// 扰民模式 所有灯光开启，蜂鸣器响起
void cmdNoisy();

#endif //BLUETOOTH_H
