#include <Arduino.h>
#include <Bluetooth.h>
#include <CardReader.h>
#include <Humid_Temp.h>
#include <Motor.h>
#include <OLED.h>


extern Motor *door;
extern Motor *window;
extern Motor *fan;

String message = "";

int command(String command) {
    Serial.println("get message: " + command);
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
    }
    else ;
    return 0;
}

String currInfo(){
    return "";
}