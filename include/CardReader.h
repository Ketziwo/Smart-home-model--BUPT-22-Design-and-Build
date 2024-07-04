//
// Created by Dai Hao on 2024/7/2.
//
#ifndef CARDREADER_H
#define CARDREADER_H

#include <MFRC522.h>
#include <PIN.h>

const String myRFID = "E3 CB 09 2D";

class CardReader{
public:
    CardReader();
    String getRFID();
private:
    MFRC522 *mfrc522;
};

#endif //CARDREADER_H
