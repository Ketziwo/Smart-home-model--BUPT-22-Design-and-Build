//
// Created by Zhang ZhuHan on 2024/7/3.
//
#include "Infrared.h"
#include <Arduino.h>

IRrecv irrecv(RECV_PIN);
decode_results results;

void infInit() {
    irrecv.enableIRIn();         // 启动红外接收
}

int infLoop() {
    int x = -1;
    if(irrecv.decode(&results)) {
        // 解码红外遥控信号
        Serial.println(results.value);
        switch(results.value) {
            case 0x488F3CBB:
                x = 0;
                break;
            case 0xFFA25D:
                x = 1;
                break;
            case 0xFF629D:
                x = 2;
                break;
            case 0xFFE21D:
                x = 3;
                break;
            case 0xFF22DD:
                x = 4;
                break;
            case 0xFF02FD:
                x = 5;
                break;
            case 0xFFC23D:
                x = 6;
                break;
        }
        irrecv.resume();   // 开始读取下一条信息
        Serial.println(x);
    }
    return x;
}