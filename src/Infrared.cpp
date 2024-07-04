//
// Created by Zhang ZhuHan on 2024/7/3.
//
// #include "Infrared.h"
//
// static IRrecv irrecv(RECV_PIN);
// decode_results *results;
//
// void infInit() {
//     irrecv.enableIRIn();        // 启动红外接收
// }
//
// int infLoop() {
//     int x = -1;
//     if (irrecv.decode(results)) {  // 解码红外遥控信号
//         switch(results->value) {
//             case 0x488F3CBB:
//                 x = 1;
//                 break;
//         }
//         irrecv.resume();   // 开始读取下一条信息
//     }
//     return x;
// }