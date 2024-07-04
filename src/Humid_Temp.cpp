//
// Created by Zhang YeXin on 2024/7/2.
//
#include "Humid_Temp.h"

// 初始化DHT传感器
myDHT::myDHT(){
    dht = new DHT(DHTPIN, DHTTYPE);
    dht->begin();
}

// 读取温湿度数据
void myDHT::getDHT() {
    humidity = dht->readHumidity();
    temperature = dht->readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      // Serial.println("读取失败！");
      humidity = NAN;
      temperature = NAN;
    }
}

float myDHT::getHumidity() {return humidity;}
float myDHT::getTemperature() {return temperature;}

String myDHT::tempToString() {
    String temp = "Temp: ";
    if (!isnan(temperature)) {
        temp += String(temperature, 2);
        temp +=" C";
    } else {
        temp += "N/A";
    }
    return temp;
}

String myDHT::humidToString() {
    String humid = "Humidity: ";
    if (!isnan(humidity)) {
        humid += String(humidity, 0);
        humid +=" %";
    } else {
        humid += "N/A";
    }
    return humid;
}

