//
// Created by Dai Hao on 2024/7/2.
//
#ifndef MOTOR_H
#define MOTOR_H

#include <pins_arduino.h>
#include <Servo.h>

const int Door_Pin = 11;
const int Window_Pin = 10;
const int Fan_Pin = 9;

class Motor {
public:
    int getState(); // 获取Motor当前的状态
    int getAuto();
    virtual void setAuto(int);
    virtual void setState(int) = 0; // 更新Motor的状态
protected:
    int state = 0; // 记录Motor的状态 0为关闭，1为开启
    int Auto = 0;
};


class Door: public Motor {
public:
    Door();
    void setState(int);
    void setAuto(int);
private:
    Servo dServo;
};

class Window: public Motor {
public:
    Window();
    void setState(int);
private:
    Servo wServo;
};

class Fan: public Motor {
public:
    Fan();
    void setState(int);
};

#endif //MOTOR_H
