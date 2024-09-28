//
// Created by Dai Hao on 2024/7/2.
//
#include <Arduino.h>
#include <CardReader.h>
#include <Clock.h>
#include <Command.h>
#include <Humid_Temp.h>
#include <Light.h>
#include <Motor.h>
#include <OLED.h>


extern Motor *door, *windowKC, *windowWS, *fanCtrl;
extern Fan* fan;
extern OLED * scr;
extern Clock * clock;

String message = "";
extern int AutoLight;

int command(String command) {
    Serial.println("command: " + command);
    command.trim(); // 掐头去尾
    command.toLowerCase(); // 转小写

    // 开门指令
    // door on 开门
    // door off 关门
    if (command.equals("door on")) {
            cmdDoor(true, 5);
            return 1;
    }
    if (command.equals("door off")) {
            cmdDoor(false);
            return 1;
    }

    // 窗户指令
    // window on 开启
    // window off 关闭
    else if (command.startsWith("window")){
        command.remove(0,7);
        bool x;
        // 判断开关
        if (command.startsWith("on")) {
            x = true;
            command.remove(0, 2);
        }
        else if (command.startsWith("off")) {
            x = false;
            command.remove(0, 3);
        }
        else {
            return 0;
        }

        // 对全屋使用
        if (command.equals("")){
            cmdWindow(x);
            return 1;
        }

        // 对特定屋使用
        command.remove(0, 1);
        if (command.equals("0")){
            cmdWindow(x, 0);
            return 1;
        }
        else if (command.equals("1")){
            cmdWindow(x, 1);
            return 1;
        }
        else if (command.equals("2")) {
            cmdWindow(x, 2);
            return 1;
        }
        else{
            return 0;
        }
    }

    // 风扇指令
    // fan on 开启
    // fan off 关闭
    else if (command.startsWith("fan")){
        command.remove(0,4);
        bool x;
        // 判断开关
        if (command.startsWith("on")) {
            x = true;
            command.remove(0, 2);
        }
        else if (command.startsWith("off")) {
            x = false;
            command.remove(0, 3);
        }
        else {
            return 0;
        }

        // 对全屋使用
        if (command.equals("")){
            cmdFan(x);
            return 1;
        }

        // 对特定屋使用
        command.remove(0, 1);
        if (command.equals("0")){
            cmdFan(x, 0);
            return 1;
        }
        else if (command.equals("1")){
            cmdFan(x, 1);
            return 1;
        }
        else if (command.equals("2")) {
            cmdFan(x, 2);
            return 1;
        }
        else if (command.equals("3")) {
            cmdFan(x, 3);
            return 1;
        }
        else{
            return 0;
        }
    }

    else if (command.startsWith("light")){
        command.remove(0,6);
        int x;

        // 判断开关
        if (command.startsWith("on")) {
            x = 1;
            command.remove(0, 2);
        }
        else if (command.startsWith("off")) {
            x = 0;
            command.remove(0, 3);
        }
        else if (command.startsWith("spark")) {
            x = 2;
            command.remove(0, 5);
        }
        else {
            return 0;
        }

        // 对全屋使用
        if (command.equals("")){
            cmdRGB(x);
            return 1;
        }
        
        // 对特定房间使用
        command.remove(0, 1);
        if (command.equals("0")) {
            cmdRGB(x, 0);
            return 1;
        }
        else if (command.equals("1")){
            cmdRGB(x, 0);
            return 1;
        }
        else if (command.equals("2")) {
            cmdRGB(x, 0);
            return 1;
        }
        else if (command.equals("3")) {
            cmdRGB(x, 0);
            return 1;
        }
        else if (command.equals("4")) {
            cmdRGB(x, 0);
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

void notifyMSG(char* BTNotifyMessage){
}

void voiceCommand(String s) {
    // 读取接收到的字符
    char receivedChar = s.charAt(0);

    // 根据接收到的字符执行对应的操作
    switch (receivedChar) {
        case 'L':
            //开灯
            command("light on");
            break;
        case 'l':
            //关灯
            command("light off");
            break;
        case 'F':
            //开风扇
            command("fan on");
            break;
        case 'f':
            //关风扇
            command("fan off");
            break;
        case 'd':
            //关门
            command("door off");
            break;
        case 'W':
            //开窗
            command("window on");
            break;
        case 'w':
            //关窗
            command("window off");
            break;
        case 'a':
            //自动风扇
            command("fan auto");
            break;
        case 'b':
            //自动灯光
            command("light auto");
            break;
        case 'c':
            //自动窗户
            command("window auto");
            break;
        case 'n':
            //全部自动
            command("light auto");
            command("window auto");
            command("fan auto");
            break;
    }
}

void cmdDoor(bool x, int time) {
    if(x) {
        door->open();
        scr->print("welcome home :D");
    } else {
        door->close();
    }
}
void cmdWindow(bool x, int id) {
    switch(id) {
    case 0:
        cmdWindow(x, 1);
        cmdWindow(x, 2);
        break;
    case 1:
        if(x) {
            windowKC->open();
        } else {
            windowKC->close();
        }
        break;
    case 2:
        if(x) {
            windowWS->open();
        } else {
            windowWS->close();
        }
        break;
    }
}
void cmdFan(bool x, int id){
    if(x) {
        fan->open();
        switch (id)
        {
        case 0:
            break;
        case 1:
            fanCtrl->angle(0);
            break;
        case 2:
            fanCtrl->angle(135);
            break;
        case 3:
            fanCtrl->angle(45);
            break;
        }
    } else {
        fanCtrl->angle(0);
        fan->close();
    }
}

void cmdRGB(int x, int id) {
    Serial.println("cmdRGB");
}

void cmdTime(int hour, int min){
    clock->printTime(hour, min);
}