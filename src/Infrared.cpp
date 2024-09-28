//
// Created by Zhang ZhuHan on 2024/7/3.
//
#include "Infrared.h"
#include <Arduino.h>

Infrared::Infrared() {
    irrecv = new IRrecv(RECV_PIN);
    irrecv->enableIRIn(); // 启动红外接收
}

char Infrared::get() {
    char x = ' ';
    if(irrecv->decode(&results)) {
        // 解码红外遥控信号
        // Serial.println(results.value);
        switch(results.value) {
            case 0xFF9867:
                x = '0';
                break;
            case 0xFFA25D:
                x = '1';
                break;
            case 0xFF629D:
                x = '2';
                break;
            case 0xFFE21D:
                x = '3';
                break;
            case 0xFF22DD:
                x = '4';
                break;
            case 0xFF02FD:
                x = '5';
                break;
            case 0xFFC23D:
                x = '6';
                break;
            case 0xFFE01F:
                x = '7';
                break;
            case 0xFFA857:
                x = '8';
                break;
            case 0xFF906F:
                x = '9';
                break;
            case 0xFF6897:
                x = '*';
                break;
            case 0xFFB04F:
                x = '#';
                break;
            case 0xFF38C7:
                x = 'k';
                break;
            case 0xFF18E7:
                x = 'u';
                break;
            case 0xFF4AB5:
                x = 'd';
                break;
            case 0xFF10EF:
                x = 'l';
                break;
            case 0xFF5AA5:
                x = 'r';
                break;
        }
        irrecv->resume();   // 开始读取下一条信息
        // Serial.println(x);
    }
    return x;
}