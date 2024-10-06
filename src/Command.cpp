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
#include <Timer.h>

extern bool Is_home;
extern Motor *door, *windowKC, *windowWS, *fanCtrl;
extern Fan* fan;
extern OLED * scr;
extern Clock * clock;
extern RGB *rgbDin, *rgbMainBed, *rgbSubBed, *rgbWash;
extern char screenmsg[20];
extern cycle cyc;

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
    else if (command.startsWith("window ")) {
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
        if (command.length() == 0){
            cmdWindow(x, 0);
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
    else if (command.startsWith("fan ")) {
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

    // 灯光控制
    else if (command.startsWith("light ")) {
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
            cmdRGB(x, 1);
            return 1;
        }
        else if (command.equals("2")) {
            cmdRGB(x, 2);
            return 1;
        }
        else if (command.equals("3")) {
            cmdRGB(x, 3);
            return 1;
        }
        else if (command.equals("4")) {
            cmdRGB(x, 4);
            return 1;
        }
        else{
            return 0;
        }
    }
    
    // 时间控制
    else if (command.startsWith("time ") && (command.length() == 10)) {
        int hh = (command.charAt(5)-'0')*10 + (command.charAt(6)-'0');
        int mm = (command.charAt(8)-'0')*10 + (command.charAt(9)-'0');
        cmdTime(hh, mm);
        return 1;
    }
    
    // 显示屏信息
    else if (command.startsWith("show ")) {
        if(command.length() > 5 && command.length() <= 25) {
            command.remove(0, 5);
            command.toCharArray(screenmsg, command.length() + 1);
        } else return 0;
    }

    else if (command.equals("imleave")) {
        cmdLeaving();
    }
    else if (command.equals("gotobed")) {
        cmdBeforeBed();
    }
    else if (command.equals("sleep")) {
        cmdSleeping();
    }
    else if (command.equals("getsomenoise")) {
        cmdNoisy();
    }
    return 0;
}

void notifyMSG(char* BTNotifyMessage){

}

void cmdDoor(bool x, int time) {
    if(x) {
        door->open();
        Is_home = true;
        if(time > 0) cyc.doorOpenTime = time*2;
        strcpy(screenmsg, "Welcome home! ^D^");
    } else {
        door->close();
    }
}

void cmdWindow(bool x, int id) {
    switch(id) {
    case 0:
        cmdWindow(x, 1);
        delay(500);
        cmdWindow(x, 2);
        break;
    case 1:
        if(x) {
            windowKC->open();
        } else {
            windowKC->close();
        }
        windowKC->Auto = false;
        break;
    case 2:
        if(x) {
            windowWS->open();
        } else {
            windowWS->close();
        }
        windowWS->Auto = false;
        break;
    }
}

void cmdFan(bool x, int id){
    cyc.fanAngle = -1;
    if(x) {
        fan->open();
        switch (id)
        {
        case 0:
            cyc.fanAngle = 0;
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
    fan->Auto = false;
}

void cmdRGB(int x, int id) {
    switch(id) {
    case 0:
        cmdRGB(x, 1);
        cmdRGB(x, 2);
        cmdRGB(x, 3);
        cmdRGB(x, 4);
        break;
    case 1:
        cyc.DinLight = -1;
        switch(x) {
        case 0:
            rgbDin->Off();
            break;
        case 1:
            rgbDin->On();
            break;
        case 2:
            cyc.DinLight = 0;
            break;
        }
        rgbDin->Auto = false;
        break;
    case 2:
        cyc.MBLight = -1;
        switch(x) {
        case 0:
            rgbMainBed->Off();
            break;
        case 1:
            rgbMainBed->On();
            break;
        case 2:
            cyc.MBLight = 0;
            break;
        }
        rgbMainBed->Auto = false;
        break;
    case 3:
        cyc.SBLight = -1;
        switch(x) {
        case 0:
            rgbSubBed->Off();
            break;
        case 1:
            rgbSubBed->On();
            break;
        case 2:
            cyc.SBLight = 0;
            break;
        }
        rgbSubBed->Auto = false;
        break;
    case 4:
        cyc.WSLight = -1;
        switch(x) {
        case 0:
            rgbWash->Off();
            break;
        case 1:
            rgbWash->On();
            break;
        case 2:
            cyc.WSLight = 0;
            break;
        }
        rgbWash->Auto = false;
        break;
    }
}

void cmdTime(int hour, int min){
    clock->printTime(hour, min);
}

void cmdBeforeBed() {
    cmdFan(true, 2);
    cmdRGB(false);
    cmdRGB(true, 2);
    strcpy(screenmsg, "Time to bed!");
}

void cmdSleeping() {
    cmdFan(true, 2);
    cmdRGB(false);
    strcpy(screenmsg, "zzz zzz zzz");
}

void cmdLeaving() {
    cmdDoor(true, 5);
    cmdWindow(false);
    cmdFan(false);
    Is_home = false;
    scr->print("");
}

void cmdNoisy() {
    cmdRGB(2);
    cmdFan(true);
}