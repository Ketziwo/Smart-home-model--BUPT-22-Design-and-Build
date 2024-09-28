//
// Created by Dai Hao on 2024/7/2.
//
#include "Motor.h"

#include <Arduino.h>


Motor::Motor(const unsigned int PIN) {
    servo = Servo();
    servo.attach(PIN);
    state = false;
}
void Motor::open() {
    servo.write(90);
    state = true;
}
void Motor::close() {
    servo.write(0);
    state = false;
}

void Motor::angle(const int a) {
    servo.write(a);
}

Fan::Fan(const unsigned int PIN) {
    pinMode(PIN, OUTPUT);
    pin = PIN;
    state = false;
}
void Fan::open() {
    digitalWrite(pin, LOW); // 开启风扇
    state = true;
}
void Fan::close() {
    digitalWrite(pin, HIGH); // 关闭风扇
    state = false;
}

// // 获取Motor当前的状态
// int Motor::getState() {
//     return state;
// }

// void Motor::open() {
//     setState(1);
// }
// void Motor::close() {
//     setState(0);
// }

// Door::Door(const unsigned int pin) {
//     dServo = Servo();
//     dServo.attach(pin);
//     setState(0);
// }


// void Door::setState(int x) {
//     switch(x){
//         case 0:
//             dServo.write(90); // 控制舵机停止
//             state = 0;
//             return;
//         case 1:
//             dServo.write(110); // 控制舵机正向旋转
//             state = 1;
//             return;
//     }
// }

// void Door::setAuto(int x) {
//     Auto = 0;
// }

// Window::Window(const unsigned int pin) {
//     wServo = Servo();
//     wServo.attach(pin);
// }

// void Window::setState(int x) {
//     switch(x){
//         case 0:
//             wServo.write(0); //控制舵机旋转到0度位置
//             state = 0;
//             return;
//         case 1:
//             wServo.write(90); //控制舵机旋转到90度位置
//             state = 1;
//             return;
//     }
// }

// Fan::Fan() {
//     pinMode(Fan_Pin, OUTPUT);
// }

// void Fan::setState(int x) {
//     switch(x){
//         case 0:
//             digitalWrite(Fan_Pin, HIGH); // 关闭风扇
//             state = 0;
//             return;
//         case 1:
//             digitalWrite(Fan_Pin, LOW); // 打开风扇
//             state = 1;
//             return;
//     }
// }
