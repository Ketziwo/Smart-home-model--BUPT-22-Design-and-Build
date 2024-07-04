//
// Created by Dai Hao on 2024/7/2.
//
#include "Motor.h"

#include <Arduino.h>

// 获取Motor当前的状态
int Motor::getState() {
    return state;
}

int Motor::getAuto() {
    return Auto;
}

void Motor::setAuto(int x) {
    Auto = x;
}

Door::Door() {
    dServo = Servo();
    dServo.attach(Door_Pin);
    setState(0);
}


void Door::setState(int x) {
    switch(x){
        case 0:
            dServo.write(90); // 控制舵机停止
            state = 0;
            return;
        case 1:
            dServo.write(120); // 控制舵机正向旋转
            state = 1;
            return;
    }
}

void Door::setAuto(int x) {
    Auto = 0;
}

Window::Window() {
    wServo = Servo();
    wServo.attach(Window_Pin);
    setAuto(1);
}

void Window::setState(int x) {
    switch(x){
        case 0:
            wServo.write(0); //控制舵机旋转到0度位置
            state = 0;
            return;
        case 1:
            wServo.write(90); //控制舵机旋转到90度位置
            state = 1;
            return;
    }
}

Fan::Fan() {
    pinMode(Fan_Pin, OUTPUT);
    setAuto(1);
}

void Fan::setState(int x) {
    switch(x){
        case 0:
            digitalWrite(Fan_Pin, HIGH); // 关闭风扇
            state = 0;
            return;
        case 1:
            digitalWrite(Fan_Pin, LOW); // 打开风扇
            state = 1;
            return;
    }
}
