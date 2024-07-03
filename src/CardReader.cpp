#include "CardReader.h"

CardReader::CardReader() {
    mfrc522 = new MFRC522(SS_PIN, RST_PIN);
    SPI.begin();           // Initiate  SPI bus
    mfrc522->PCD_Init();    // Initiate MFRC522
}

String CardReader::getRFID() {
    if (!mfrc522->PICC_IsNewCardPresent()) return "";
    if (!mfrc522->PICC_ReadCardSerial()) return "";
    // Serial.print("UID tag :");
    String content= "";
    for (byte i = 0; i < mfrc522->uid.size; i++)
    {
        // Serial.print(mfrc522->uid.uidByte[i] < 0x10 ? " 0" : " ");
        // Serial.print(mfrc522->uid.uidByte[i], HEX);
        content.concat(String(mfrc522->uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522->uid.uidByte[i], HEX));
    }
    // Serial.println();
    // Serial.print("Message : ");
    content.toUpperCase();
    return content.substring(1);  //“ ”中输入IC卡的ID信息即可识别解锁
}