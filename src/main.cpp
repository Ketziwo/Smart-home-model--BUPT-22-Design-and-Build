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

#include <MsTimer2.h>

// 初始化对象
bool Is_home;
Motor *door, *windowKC, *windowWS, *fanCtrl;
Fan* fan;
CardReader * cardReader;
Clock * clock;
myDHT * dht;
OLED * scr;
RGB *rgbDin, *rgbMainBed, *rgbSubBed, *rgbWash;
Infrared * infrared;

char BTNotifyMessage[48] = {0};

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
    scr->print("");
    // rgbDin = new RGB(DIN_G_PIN, DIN_R_PIN, DIN_B_PIN, false);
    // rgbMainBed = new RGB(MBED_G_PIN, MBED_R_PIN, MBED_B_PIN, false);
    // rgbSubBed = new RGB(SBED_G_PIN, SBED_R_PIN, SBED_B_PIN, false);
    // rgbWash = new RGB(WASH_G_PIN, WASH_R_PIN, WASH_B_PIN, false);
    infrared = new Infrared();
    
    DoorbellInit();
    Beep(1);
    // flameInit();
}

void loop() {

    // 接收蓝牙信息并执行命令
    if(Serial.available()) {command(Serial.readString());}
    if(Serial1.available()) {command(Serial1.readString());}

    clock->printTime(12, 30);
    // if(Serial2.available()){
    //     String msg = Serial1.readString();
    //     Serial.println("recv msg: " + msg);
    //     voiceCommand(msg);
    // }

    /* 
    默认技能模块：
    包含读卡器开门，门铃，火灾传感器
    */
    // 如果检测到读卡器内容与我的读卡器相同 则开门
    if(myRFID == cardReader->getRFID()) {
        scr->print("welcome home");
        delay(1000);
        command("door on");
        // clock->print(1000);
    }

    // 检测压感并触发蜂鸣器
    if(getDoorbell()) Beep(200, 1, 1);

    // if(Is_home) {
    //     ...;
    // }

    // 如果温度高于30度，则开启风扇
    dht->getDHT();

    // Serial.println(mydht->getTemperature());
    // if(1){
    //     if (dht->getTemperature() > 30) {
    //         fan->open(); // 打开风扇
    //     }
    //     else {
    //         fan->close(); // 关闭风扇
    //     }
    // }

    // // 雨滴传感器 监测是否下雨以关闭窗户
    // // Serial.println(analogRead(RAIN_PIN));
    // if(window->getAuto()) {
    //     if (analogRead(RAIN_PIN) < 800) window->setState(0); //关闭窗户
    //     else window->setState(1);
    // }


    // // 用OLED屏幕显示温湿度
    // u8g.firstPage();
    // do {
    //     draw(mydht->tempToString(), 0);
    //     draw(mydht->humidToString(), 1);
    //     if(AutoLight)
    //         draw("light: auto",2);
    //     else
    //         draw("light: manual",2);
    //     if(fan->getAuto())
    //         draw("fan: auto",3);
    //     else
    //         draw("fan: manual",3);
    //     if(window->getAuto())
    //         draw("window: auto",4);
    //     else
    //         draw("window: manual",4);
    // } while (u8g.nextPage());

    // displayNum(1024 - analogRead(LIGHT_PIN));
    // if (AutoLight == 1) {
    //     if(analogRead(LIGHT_PIN) > 800) displayRGB(0, 1, 1, 1);
    //     else displayRGB(0, 0, 0, 0);
    // }
    // if(!getFlame()) Beep(200, 10, 1);

    // switch(infLoop()) {
    //     case 1:
    //         displayRGB(0,1, 1, 1);
    //         AutoLight = 0;
    //         break;
    //     case 2:
    //         command("fan on");
    //         break;
    //     case 3:
    //         command("window on");
    //         break;
    //     case 4:
    //         displayRGB(0,0, 0, 0);
    //         AutoLight = 0;
    //         break;
    //     case 5:
    //         command("fan off");
    //         break;
    //     case 6:
    //         command("window off");
    //         break;
    // }

    // switch(infrared->get()) {
    //     case '#': 
    //         break;
    // }
    char c = infrared->get();
    if(c != ' '){
        if(c == 'k'){door->open();}
        else if (c == '*'){door->close();}
        static char msg[20] = " ";
        static int msgsize = 0;
        msg[msgsize++] = c;
        Serial.println(msg);
        scr->print(msg);
    }
}


