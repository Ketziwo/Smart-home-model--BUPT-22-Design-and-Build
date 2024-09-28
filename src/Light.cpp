//
// Created by Ma YiRan on 2024/7/3.
//
#include "Light.h"
#include <Arduino.h>


// int AutoLight = 1;

// void initLight() {
//     pinMode(R_PIN, OUTPUT);
//     pinMode(G_PIN, OUTPUT);
//     pinMode(B_PIN, OUTPUT);
//     display.begin(); // 初始化数码管
//     display.setBacklight(100); // 设置数码管亮度为 100%
// }
// void displayNum(int num) {
//     if(num > 9999) num = 9999;
//     else if(num < -999) num = -999;
//     display.clear();
//     display.print(num); //数码管显示 A0 模拟值
// }
// void displayRGB(int change, int R, int G, int B) {
//     static int state = 0;
//     if(change) {
//         state = !state;
//         digitalWrite(R_PIN, state);
//         digitalWrite(G_PIN, state);
//         digitalWrite(B_PIN, state);
//     }
//     else {
//         digitalWrite(R_PIN, R);
//         digitalWrite(G_PIN, G);
//         digitalWrite(B_PIN, B);
//     }
// }

RGB::RGB(const unsigned int G_pin, const unsigned int R_pin, const unsigned int B_pin, bool is_Analog):G_PIN(G_pin), R_PIN(R_pin), B_PIN(B_pin) {
    pinMode(G_PIN, OUTPUT);
    pinMode(R_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
    Is_Analog = is_Analog;
}

void RGB::On() {
    digitalWrite(G_PIN, HIGH);
    digitalWrite(R_PIN, HIGH);
    digitalWrite(B_PIN, HIGH);
    Is_Auto = false;
}
void RGB::On(int G, int R, int B) {
    if(!Is_Analog) {
        digitalWrite(G_PIN, G);
        digitalWrite(R_PIN, R);
        digitalWrite(B_PIN, B);
    }
    else{
        analogWrite(G_PIN, G);
        analogWrite(R_PIN, R);
        analogWrite(B_PIN, B);
    }
    Is_Auto = false;
}
void RGB::Off() {
    digitalWrite(G_PIN, 0);
    digitalWrite(R_PIN, 0);
    digitalWrite(B_PIN, 0);
    Is_Auto = false;
}

void RGB::Auto() {
    Is_Auto = true;
}

bool RGB::get_Auto() {
    return Is_Auto;
}