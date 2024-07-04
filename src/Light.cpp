//
// Created by Ma YiRan on 2024/7/3.
//
#include "Light.h"

SevenSegmentTM1637 display(CLK_PIN, DIO_PIN);
int AutoLight = 1;

void initLight() {
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
    display.begin(); // 初始化数码管
    display.setBacklight(100); // 设置数码管亮度为 100%
}
void displayNum(int num) {
    if(num > 9999) num = 9999;
    else if(num < -999) num = -999;
    display.clear();
    display.print(num); //数码管显示 A0 模拟值
}
void displayRGB(int change, int R, int G, int B) {
    static int state = 0;
    if(change) {
        state = !state;
        digitalWrite(R_PIN, state);
        digitalWrite(G_PIN, state);
        digitalWrite(B_PIN, state);
    }
    else {
        digitalWrite(R_PIN, R);
        digitalWrite(G_PIN, G);
        digitalWrite(B_PIN, B);
    }
}