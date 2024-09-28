//
// Created by Zhang YeXin on 2024/7/2.
//
#ifndef OLED_H
#define OLED_H

#include <U8glib.h>

// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); // SCL；SDA

class OLED {
public:
    OLED();
    void print(char str[]);
    void print(char strs[][20], int size);    
private:
    // OLED显示屏设置
    U8GLIB_SSD1306_128X64 *u8g;
};



#endif //OLED_H
