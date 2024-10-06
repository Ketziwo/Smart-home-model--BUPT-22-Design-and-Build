//
// Created by Zhang ZhuHan on 2024/7/3.
//
#ifndef INFRARED_H
#define INFRARED_H

#include <IRremote.h> // 引入红外解码库
#include <PIN.h>

class Infrared {
public:
    Infrared();
    char get();
private:
    static IRrecv irrecv;
    decode_results results;
};

#endif //INFRARED_H
