#include <Arduino.h>
#include <Bluetooth.h>
#include <CardReader.h>
#include <Doorbell.h>
#include <Humid_Temp.h>
// #include <Infrared.h>
#include <Light.h>
#include <Motor.h>
#include <OLED.h>
#include <SoftwareSerial.h>
// SoftwareSerial BT(7, 6);

// 初始化对象
Motor *door;
Motor *window;
Motor *fan;
CardReader *cardReader; // cardreader对象初始化
myDHT *mydht;
extern U8GLIB_SSD1306_128X64 u8g;

void setup() {
    Serial.begin(9600); // 定义电脑串口波特率

    door = new Door();
    window = new Window();
    fan = new Fan();
    cardReader = new CardReader(); // cardreader对象初始化
    mydht = new myDHT();
    initLight();
    DoorbellInit();
    // infInit();

    fan->setAuto(0);
    fan->setState(0);
    Beep(1);
}

void loop() {
    // 接收蓝牙信息并执行命令
    if(Serial.available()) {command(Serial.readString());}
    // if(BT.available()) {
    //     String msg = "";
    //     while(BT.available()) {
    //          msg +=BT.read();
    //     }
    //     command(msg);
    // }

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

    displayLight(analogRead(LIGHT_PIN));
    // Serial.println(analogRead(A2));

    if(digitalRead(BELL_PIN))
        Beep(200);

    // if(infLoop() == 1) {
    //     fan->setState(!fan->getState());
    // }
}


