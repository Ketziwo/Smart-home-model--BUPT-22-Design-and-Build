#include "Light.h"

SevenSegmentTM1637 display(CLK_PIN, DIO_PIN);

void initLight() {
    display.begin(); // 初始化数码管
    display.setBacklight(100); // 设置数码管亮度为 100%
}
void displayLight() {
    display.clear();
    display.print(1000); //数码管显示 A0 模拟值
}