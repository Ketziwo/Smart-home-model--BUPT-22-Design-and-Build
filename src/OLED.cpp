//
// Created by Zhang YeXin on 2024/7/2.
//
#include "OLED.h"



OLED::OLED() {
    u8g = new U8GLIB_SSD1306_128X64(U8G_I2C_OPT_NONE);
}

// 绘制OLED显示内容

void OLED::print(char str[]) {
    u8g->setFont(u8g_font_6x10);
    u8g->firstPage();
        do {
            u8g->setPrintPos(10, 10);
            u8g->print(str);
        } while (u8g->nextPage());
}

void OLED::print(char strs[][20], int size) {
    // int size = sizeof(strs)/sizeof(strs[0]);
    u8g->setFont(u8g_font_6x10);
    u8g->firstPage();
    do {
        for(int i = 0; i < size; ++i) {
            u8g->setPrintPos(10, 10*i+10);
            u8g->print(strs[i]);
        }
    } while (u8g->nextPage());
}
