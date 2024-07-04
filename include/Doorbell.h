//
// Created by Ma YiRan on 2024/7/3.
//
#ifndef DOORBELL_H
#define DOORBELL_H
#include <PIN.h>

void DoorbellInit();
int getDoorbell();
void Beep(int time, int freq1 = 2, int freq2 = 1);


#endif //DOORBELL_H
