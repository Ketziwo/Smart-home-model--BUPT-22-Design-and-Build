//
// Created by Zhang YeXin on 2024/7/2.
//
#ifndef HUMID_TEMP_H
#define HUMID_TEMP_H

#include <DHT.h>
#include <PIN.h>

const unsigned int DHTTYPE = DHT11; // DHT11传感器

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
