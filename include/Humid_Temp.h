#ifndef HUMID_TEMP_H
#define HUMID_TEMP_H

#include <DHT.h>


// DHT传感器设置
const unsigned int DHTPIN = A0; // DHT11数据引脚连接到数字引脚7
const unsigned int DHTTYPE = DHT11; // DHT11传感器

const unsigned int RAIN_PIN = A1; // 雨滴传感器

class myDHT {
public:
    myDHT();
    void getDHT();
    float getHumidity();
    float getTemperature();
    String tempToString();
    String humidToString();
private:
    DHT *dht;
    float humidity = 0;
    float temperature = 0;
};

#endif //HUMID_TEMP_H
