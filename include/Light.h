//
// Created by Ma YiRan on 2024/7/3.
//
#ifndef LIGHT_H
#define LIGHT_H

#include <PIN.h>

class RGB {
public:
    RGB(const unsigned int G_Pin, const unsigned int R_Pin, const unsigned int B_Pin, bool is_Analog);
    void On();
    void On(int G, int R, int B);
    void Off();
    bool state;
    bool Auto;
private:
    unsigned int G_PIN, R_PIN, B_PIN;
};

// void displayNum(int);

#endif //LIGHT_H
