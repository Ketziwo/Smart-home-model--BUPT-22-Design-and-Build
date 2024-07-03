#ifndef DOORBELL_H
#define DOORBELL_H

const unsigned int BELL_PIN = 4; //设置按键输出到 2 号引脚
const unsigned int BEEP_PIN = 6; //设置蜂鸣器控制引脚为 8 号

void DoorbellInit();
void Beep(int time, int freq1 = 2, int freq2 = 1);


#endif //DOORBELL_H
