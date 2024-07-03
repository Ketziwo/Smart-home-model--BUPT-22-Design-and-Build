#ifndef CARDREADER_H
#define CARDREADER_H

#include <MFRC522.h>

const unsigned int RST_PIN = 5;
const unsigned int SS_PIN = 53;

const String myRFID = "E3 CB 09 2D";

class CardReader{
public:
    CardReader();
    String getRFID();
private:
    MFRC522 *mfrc522;
};

#endif //CARDREADER_H
