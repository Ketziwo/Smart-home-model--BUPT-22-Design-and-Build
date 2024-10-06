//
// Created by Dai Hao on 2024/7/2.
//
#ifndef MOTOR_H
#define MOTOR_H

#include <pins_arduino.h>
#include <Servo.h>
#include <PIN.h>


class Motor {
public:
    bool Auto;
    bool state;
    Motor(const unsigned int);
    void open();
    void close();
    void angle(const int);
private:
    Servo servo;
};

class Fan {
public:
    bool Auto = true;
    bool state;
    Fan(const unsigned int);
    void open();
    void close();
private:
    unsigned int pin;
};

// class Motor {
// public:
//     int Auto = 0;
//     int state = 0;
//     int getState(); // 获取Motor当前的状态
//     // int getAuto();
//     void open();
//     void close();
//     // virtual void setAuto(int);
//     virtual void setState(int) = 0; // 更新Motor的状态
// // protected:
// //     int state = 0; // 记录Motor的状态 0为关闭，1为开启
// };


// class Door: public Motor {
// public:
//     Door(const unsigned int pin);
//     void setState(int);
//     void setAuto(int);
// private:
//     Servo dServo;
// };

// class Window: public Motor {
// public:
//     Window(const unsigned int pin);
//     void setState(int);
// private:
//     Servo wServo;
// };

// class Fan: public Motor {
// public:
//     Fan();
//     void setState(int);
// };

#endif //MOTOR_H
