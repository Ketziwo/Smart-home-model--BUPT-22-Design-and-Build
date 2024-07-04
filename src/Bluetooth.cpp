//
// Created by Dai Hao on 2024/7/2.
//
#include <Arduino.h>
#include <Bluetooth.h>
#include <CardReader.h>
#include <Humid_Temp.h>
#include <Light.h>
#include <Motor.h>
#include <OLED.h>


extern Motor *door;
extern Motor *window;
extern Motor *fan;

String message = "";
extern int AutoLight;

int command(String command) {
    Serial.println("recv message: " + command);
    command.trim();
    command.toLowerCase();

    // 开门指令
    // door on + password 开门
    // door off 关门
    if (command.startsWith("door")) {
        command.remove(0,5);
        if (command.equals("off")) {
            door->setState(0);
            return 1;
        }
        if (command.equals("on " + password)) {
            door->setState(1);
            return 1;
        }
        return 0;
    }

    // 窗户指令
    // window on 开启
    // window off 关闭
    else if (command.startsWith("window")){
        command.remove(0,7);
        if(command.equals("on")) {
            window->setState(1);
            window->setAuto(0);
            return 1;
        }
        if(command.equals("off")) {
            window->setState(0);
            window->setAuto(0);
            return 1;
        }
        if(command.equals("auto")) {
            window->setAuto(1);
            return 1;
        }
        return 0;
    }

    // 风扇指令
    // fan on 开启
    // fan off 关闭
    else if (command.startsWith("fan")){
        command.remove(0,4);
        if(command.equals("on")) {
            fan->setState(1);
            fan->setAuto(0);
            return 1;
        }
        if(command.equals("off")) {
            fan->setState(0);
            fan->setAuto(0);
            return 1;
        }
        if(command.equals("auto")) {
            fan->setAuto(1);
            return 1;
        }
        return 0;
    }

    else if (command.startsWith("light")){
        command.remove(0,6);
        if(command.equals("on")) {
            displayRGB(0, 1, 1, 1);
            AutoLight = 0;
            return 1;
        }
        if (command.equals("off")) {
            displayRGB(0, 0, 0, 0);
            AutoLight = 0;
            return 1;
        }
        if(command.equals("auto")) {
            AutoLight = 1;
            return 1;
        }
    }
    else ;
    return 0;
}

String currInfo(){
    return "";
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
