//
// Created by Zhang YeXin on 2024/7/2.
//
#include "OLED.h"

// OLED显示屏设置
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); // SCL-A5；SDA-A4

// 绘制OLED显示内容
void draw(String str, int line) {
    u8g.setFont(u8g_font_6x10);
    u8g.setPrintPos(10, 10*line + 10);
    u8g.print(str);
}
