#include <Arduino.h>
#include <Bluetooth.h>
#include <CardReader.h>
#include <Doorbell.h>
#include <Flame.h>
#include <Humid_Temp.h>
#include <Infrared.h>
#include <Light.h>
#include <Motor.h>
#include <OLED.h>

// 初始化对象
Motor *door;
Motor *window;
Motor *fan;
CardReader *cardReader; // cardreader对象初始化
myDHT *mydht;
extern U8GLIB_SSD1306_128X64 u8g;
extern int AutoLight;

void setup() {
    Serial.begin(9600); // 定义电脑串口波特率
    Serial2.begin(9600);

    door = new Door();
    window = new Window();
    fan = new Fan();
    cardReader = new CardReader(); // cardreader对象初始化
    mydht = new myDHT();
    initLight();
    DoorbellInit();
    flameInit();
    infInit();

    fan->setAuto(0);
    fan->setState(0);
    Beep(1);
}

void loop() {
    // 接收蓝牙信息并执行命令
    if(Serial.available()) {command(Serial.readString());}
    if(Serial2.available()) {command(Serial2.readString());}

    // 如果检测到读卡器内容与我的读卡器相同 则开门3秒
    if(myRFID == cardReader->getRFID()) {
        door->setState(true);
        delay(3000);
        door->setState(false);
    }

    // 如果温度高于30度，则开启风扇
    mydht->getDHT();
    // Serial.println(mydht->getTemperature());
    if(fan->getAuto()){
        if (mydht->getTemperature() > 30) {
            fan->setState(1); // 打开风扇
        }
        else {
            fan->setState(0); // 关闭风扇
        }
    }

    // 雨滴传感器 监测是否下雨以关闭窗户
    // Serial.println(analogRead(RAIN_PIN));
    if(window->getAuto()) {
        if (analogRead(RAIN_PIN) < 800) window->setState(0); //关闭窗户
        else window->setState(1);
    }


    // 用OLED屏幕显示温湿度
    u8g.firstPage();
    do {
        draw(mydht->tempToString(), 0);
        draw(mydht->humidToString(), 1);
    } while (u8g.nextPage());

    displayNum(analogRead(LIGHT_PIN));
    if (analogRead(LIGHT_PIN) > 800) displayRGB();

    if(getDoorbell()) Beep(200, 1, 1);
    if(getFrame()) Beep(200, 10, 1);

    switch(infLoop()) {
        case 1:
            displayRGB(1);
            break;
        case 2:
            fan->setState(!fan->getState());
            break;
        case 3:
            window->setState(!window->getState());
            break;
        case 4:
            AutoLight = !AutoLight;
            break;
        case 5:
            fan->setAuto(!fan->getAuto());
            break;
        case 6:
            window->setAuto(!window->getAuto());
            break;
    }
}


