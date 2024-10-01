//
// Created by Ma YiRan on 2024/7/3.
//
#include "Light.h"
#include <Arduino.h>

RGB::RGB(const unsigned int G_pin, const unsigned int R_pin, const unsigned int B_pin, bool is_Analog):G_PIN(G_pin), R_PIN(R_pin), B_PIN(B_pin) {
    pinMode(G_PIN, OUTPUT);
    pinMode(R_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
}

void RGB::On() {
    On(1, 1, 1);
    state = true;
}
void RGB::On(int G, int R, int B) {
    digitalWrite(G_PIN, G);
    digitalWrite(R_PIN, R);
    digitalWrite(B_PIN, B);
    state = true;
}
void RGB::Off() {
    On(0, 0, 0);
    state = false;
}
