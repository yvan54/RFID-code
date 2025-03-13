#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 3   // SS (SDA) connected to GP3
#define RST_PIN 5  // RST connected to GP5

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Initializing RFID...");

    SPI.setRX(4);  
    SPI.setTX(7);  
    SPI.setSCK(6); 
    SPI.begin(); 

    mfrc522.PCD_Init();
    Serial.println("RFID Ready. Scan a tag...");
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    Serial.print("Tag UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    mfrc522.PICC_HaltA();
}
