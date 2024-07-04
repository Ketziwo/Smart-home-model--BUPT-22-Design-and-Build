//
// Created by Ma YiRan on 2024/7/3.
//
#include "Doorbell.h"
#include <Arduino.h>

void DoorbellInit() {
    pinMode(BELL_PIN, INPUT); //设置该接口为输入模式
    pinMode(BEEP_PIN, OUTPUT); //设置该接口为输出模式
}

int getDoorbell() {
    return digitalRead(BELL_PIN);
}

void Beep(int time, int freq1, int freq2) {
    for(int i = 0; i < time/(freq1 + freq2) + 1; ++i) {
        digitalWrite(BEEP_PIN, LOW);
        delay(freq1);
        digitalWrite(BEEP_PIN, HIGH);
        delay(freq2);
    }
}