#include <Arduino.h>
#include <CardReader.h>
#include <Clock.h>
#include <Command.h>
#include <Doorbell.h>
#include <Flame.h>
#include <Humid_Temp.h>
#include <Infrared.h>
#include <Light.h>
#include <Motor.h>
#include <OLED.h>
#include <Timer.h>

#include <MsTimer2.h>

#include <string.h>

const char password[5] = "2580";

// 初始化对象
bool Is_home = true;
Motor *door, *windowKC, *windowWS, *fanCtrl;
Fan* fan;
CardReader * cardReader;
Clock * clock;
myDHT * dht;
OLED * scr;
RGB *rgbDin, *rgbMainBed, *rgbSubBed, *rgbWash;
Infrared * infrared;

char BTNotifyMessage[48] = {0};
char screenmsg[20] = {' '};

void setup() {
    Serial.begin(9600); // 定义电脑串口波特率
    Serial1.begin(9600); // 定义蓝牙串口波特率
    Serial2.begin(9600); // 定义语音助手串口波特率

    door  = new Motor(Door_PIN);
    windowKC = new Motor(WindowKC_PIN);
    windowWS = new Motor(WindowWS_PIN);
    fanCtrl = new Motor(Fan_CTRL);
    fan = new Fan(Fan_PIN);
    door->close();
    fanCtrl->close();
    fan->close();

    cardReader = new CardReader(); // cardreader对象初始化
    clock = new Clock();
    dht = new myDHT();
    scr = new OLED();
    clock->printTime(23, 59);
    clock->printTime(23, 59);
    scr->print("");
    rgbDin = new RGB(DIN_G_PIN, DIN_R_PIN, DIN_B_PIN, false);
    rgbMainBed = new RGB(MBED_G_PIN, MBED_R_PIN, MBED_B_PIN, false);
    rgbSubBed = new RGB(SBED_G_PIN, SBED_R_PIN, SBED_B_PIN, false);
    rgbWash = new RGB(WASH_G_PIN, WASH_R_PIN, WASH_B_PIN, false);
    infrared = new Infrared();
    
    pinMode(LIGHT_PIN, INPUT);
    DoorbellInit();
    flameInit();
    Beep(1);

    MsTimer2::set(500, cycling);
    MsTimer2::start();
}

void loop() {

    // 接收蓝牙信息并执行命令
    if(Serial.available()) {command(Serial.readString());}
    if(Serial1.available()) {command(Serial1.readString());}
    if(Serial2.available()){command(Serial2.readString());}

    /* 
    默认技能模块：
    包含读卡器开门，门铃，火灾传感器，红外控制模块
    */////////////////////////////////////////////////////////////////////////////////////////////////////

    // 检测压感并触发蜂鸣器
    if(getDoorbell()) Beep(200, 1, 1);

    // 读卡器模块：如果检测到读卡器内容与我的读卡器相同 则开门
    if(myRFID == cardReader->getRFID()) {
        delay(1000);
        command("door on");
        strcpy(screenmsg, "welcome home! :D");
    }

    // 红外+OLED 密码锁
    static int inframode = 0; // 显示屏模式，默认0显示温湿度，1输入密码，2进入菜单，3进入智能控制，4进入窗户控制，5进入灯光控制
    static char screenstr[5][20] = {' '}; // 显示屏显示内容
    char infrachar = infrared->get();
        // 在默认界面输入#进入密码锁模式
    if ((infrachar == '#' && inframode == 0) || (infrachar != ' ' && inframode == 1)) {

        strcpy(screenstr[0], "--enter password--");
        strcpy(screenstr[1], "       ----       ");
        inframode = 1;

        // 暂存已经输入的密码
        static char enteringstr[5] = "----";
        static int enteringsize = 0;

        // 若输入的是*则退出密码锁模式
        if(infrachar == '*') {
            strcpy(enteringstr, "----");
            enteringsize = 0;
            inframode = 0;
        } else if (infrachar >= '0' && infrachar <= '9') {
            // 若输入的是数字则存入输入密码槽
            enteringstr[enteringsize] = infrachar;
            ++enteringsize;
        }

        // 已经输入的密码记为*
        for(int i = 0; i < enteringsize; ++i) {
            screenstr[1][i+7] = '*';
        }

        // 输入满4位检验并开门
        if(enteringsize >= 4) {
            if(strcmp(password, enteringstr) == 0) {
                cmdDoor(true);
                strcpy(screenmsg, "welcome home! :D");
            } else{
                strcpy(screenmsg, "wrong password T_T");
            }
            strcpy(enteringstr, "----");
            enteringsize = 0;
            inframode = 0;
        } else {
            scr->print(screenstr, 2);
        }
    }

    // 火灾传感器，当火灾发生时，打开所有门窗，所有灯光闪烁，蜂鸣器响起
    // Serial.print("getFlame = ");
    // Serial.println(getFlame());
    static bool flameFlag = false;
    if (getFlame() && !flameFlag) {
        cmdDoor(true, 0);
        Beep(200, 10, 1);
        delay(400);
        Beep(200, 10, 1);
        cmdWindow(true);
        cmdRGB(2);
        cmdFan(false);
        strcpy(screenmsg, "on Fire!!!!");
        flameFlag = true;
    } else if (getFlame()) {
        Beep(200, 10, 1);
    } else if (flameFlag){
        flameFlag = false;
        strcpy(screenmsg, "");
        cmdDoor(false);
        cmdRGB(0);
    }

    /*
    被动技能模块，当有人在家时开启
    包括光感、雨水、温湿度传感，显示屏
    */////////////////////////////////////////////////////////////////////////////////////////////////////
    if(Is_home) {

        dht->getDHT();
        int humid = dht->getHumidity()*100;
        int temp = dht->getTemperature()*10;
        int rain = !digitalRead(RAIN_PIN); // 1则关闭窗户
        int light = analogRead(LIGHT_PIN); // 大于800则开灯

        // 传感器自动模块
        {    
            // 风扇自动模式
            if (fan->Auto == false && ((temp < 300 && fan->state == false) || (temp >= 300 && fan->state == true))) {
                // 当风扇状态与温度一致时，设置风扇为自动模式
                fan->Auto = true;
            } else if (temp >= 300 && fan->state == false && fan->Auto) {
                cmdFan(true);
                fan->Auto = true;
            } else if (temp < 300 && fan->state == true && fan->Auto) {
                cmdFan(false);
                fan->Auto = true;
            }

            // 窗户自动模式
            if (windowKC->Auto == false && ((rain && windowKC->state == false) || (!rain && windowKC->state == true))) {
                // 当厨房窗状态与是否下雨一致时，设置厨房窗为自动模式
                windowKC->Auto = true;
            } else if (!rain && windowKC->state == false && windowKC->Auto) {
                cmdWindow(true, 1);
                delay(400);
                windowKC->Auto = true;
            } else if (rain && windowKC->state == true && windowKC->Auto) {
                cmdWindow(false, 1);
                delay(400);
                windowKC->Auto = true;
            }
            
            if (windowWS->Auto == false && ((rain && windowWS->state == false) || (!rain && windowWS->state == true))) {
                // 当厕所窗状态与是否下雨一致时，设置厕所窗为自动模式
                windowWS->Auto = true;
            } else if (!rain && windowWS->state == false && windowWS->Auto) {
                cmdWindow(true, 2);
                windowWS->Auto = true;
            } else if (rain && windowWS->state == true && windowWS->Auto) {
                cmdWindow(false, 2);
                windowWS->Auto = true;
            }

            // 灯光自动模式
            if (rgbDin->Auto == false && ((light < 800 && rgbDin->state == false) || (light >= 800 && rgbDin->state == true))) {
                // 当灯光状态与室外亮度一致时，设置灯光为自动模式
                rgbDin->Auto = true;
            } else if (light >= 800 && rgbDin->state == false && rgbDin->Auto) {
                cmdRGB(true, 1);
                rgbDin->Auto = true;
            } else if (light < 800 && rgbDin->state == true && rgbDin->Auto) {
                cmdRGB(false, 1);
                rgbDin->Auto = true;
            }
            if (rgbMainBed->Auto == false && ((light < 800 && rgbMainBed->state == false) || (light >= 800 && rgbMainBed->state == true))) {
                // 当灯光状态与室外亮度一致时，设置灯光为自动模式
                rgbMainBed->Auto = true;
            } else if (light >= 800 && rgbMainBed->state == false && rgbMainBed->Auto) {
                cmdRGB(true, 2);
                rgbMainBed->Auto = true;
            } else if (light < 800 && rgbMainBed->state == true && rgbMainBed->Auto) {
                cmdRGB(false, 2);
                rgbMainBed->Auto = true;
            }
            if (rgbSubBed->Auto == false && ((light < 800 && rgbSubBed->state == false) || (light >= 800 && rgbSubBed->state == true))) {
                // 当灯光状态与室外亮度一致时，设置灯光为自动模式
                rgbSubBed->Auto = true;
            } else if (light >= 800 && rgbSubBed->state == false && rgbSubBed->Auto) {
                cmdRGB(true, 3);
                rgbSubBed->Auto = true;
            } else if (light < 800 && rgbSubBed->state == true && rgbSubBed->Auto) {
                cmdRGB(false, 3);
                rgbSubBed->Auto = true;
            }
            if (rgbWash->Auto == false && ((light < 800 && rgbWash->state == false) || (light >= 800 && rgbWash->state == true))) {
                // 当灯光状态与室外亮度一致时，设置灯光为自动模式
                rgbWash->Auto = true;
            } else if (light >= 800 && rgbWash->state == false && rgbWash->Auto) {
                cmdRGB(true, 4);
                rgbWash->Auto = true;
            } else if (light < 800 && rgbWash->state == true && rgbWash->Auto) {
                cmdRGB(false, 4);
                rgbWash->Auto = true;
            }
        }

        // OLED默认显示模式，温湿度+一条信息
        if(inframode == 0) {

            strcpy(screenstr[0], "humidity: 00.00%");
            strcpy(screenstr[1], "temperature: 00.0C");
            strcpy(screenstr[2], "");
            strcpy(screenstr[3], screenmsg);

            screenstr[0][10] = (humid/1000) + '0';
            screenstr[0][11] = (humid%1000/100) + '0';
            screenstr[0][13] = (humid%100/10) + '0';
            screenstr[0][14] = (humid%10) + '0';

            screenstr[1][13] = (temp/100) + '0';
            screenstr[1][14] = (temp%100/10) + '0';
            screenstr[1][16] = (temp%10) + '0';

            scr->print(screenstr, 4);
        }

        // 进入菜单
        if(infrachar != ' ') {
            // 按*返回上一级，提前切换mode
            if(infrachar == '*'){
                switch(inframode) {
                case 0:inframode = 2;break;
                case 2:inframode = 0;break;
                case 3:inframode = 2;break;
                case 4:inframode = 2;break;
                case 5:inframode = 2;break;
                }
            } else if (inframode == 2) {
                switch(infrachar) {
                case '1':inframode = 3;break;
                case '2':inframode = 4;break;
                case '3':inframode = 5;break;
                }
            }

            // OLED显示
            switch(inframode) {
            case 2:
                // 目录
                strcpy(screenstr[0], "1.Intelligence mode");
                strcpy(screenstr[1], "2.Window control");
                strcpy(screenstr[2], "3.Light control");
                scr->print(screenstr, 3);
                break;
            case 3:
                // 智慧模式 进入休息/睡眠/扰民/出门状态
                strcpy(screenstr[0], "1.Before bed");
                strcpy(screenstr[1], "2.I'm Sleepy");
                strcpy(screenstr[2], "3.I'm leaving");
                strcpy(screenstr[3], "4.HAVING FUN!!!");
                scr->print(screenstr, 4);
                switch(infrachar) {
                case '0':inframode = 0;break;
                case '1':inframode = 0;break;
                case '2':inframode = 0;break;
                case '3':inframode = 0;break;
                }
                break;
            case 4:
                // 窗户控制
                strcpy(screenstr[0], "1.Kitchen wnd open");
                strcpy(screenstr[1], "2.Kitchen wnd close");
                strcpy(screenstr[2], "3.Washwoom wnd open");
                strcpy(screenstr[3], "4.Washwoom wnd clos");
                scr->print(screenstr, 4);
                switch(infrachar) {
                case '0':cmdWindow(true, 2);inframode = 0;break;
                case '1':cmdWindow(false, 2);inframode = 0;break;
                case '2':cmdWindow(true, 3);inframode = 0;break;
                case '3':cmdWindow(false, 3);inframode = 0;break;
                }
                break;
            case 5:
                // 灯光控制
                strcpy(screenstr[0],"1.dinning Light");
                strcpy(screenstr[1],"2.Main-Bedroom Light");
                strcpy(screenstr[2],"3.Sec-Bedroom Light");
                strcpy(screenstr[3],"4.Washroom Light");
                scr->print(screenstr, 4);
                switch(infrachar) {
                case '0':rgbDin->state?cmdRGB(0, 1):cmdRGB(1, 1);inframode = 0;break;
                case '1':rgbMainBed->state?cmdRGB(0, 2):cmdRGB(1, 2);inframode = 0;break;
                case '2':rgbSubBed->state?cmdRGB(0, 3):cmdRGB(1, 3);inframode = 0;break;
                case '3':rgbWash->state?cmdRGB(0, 4):cmdRGB(1, 4);inframode = 0;break;
                }
                break;
            }
        }
    }
}


