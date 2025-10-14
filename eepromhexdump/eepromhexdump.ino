#include <EEPROM.h>

const int bytesPerLine = 16;
const int length = EEPROM.length();

void setup() {
  Serial.begin(115200);

  Serial.println("===READING EEPROM===");

  for(int address = 0; address < length; address += bytesPerLine) {
    if(address > 0 && address % 256 == 0) {
      Serial.println("Press ENTER to continue...");
      while(!Serial.available()) {
        ;
      }
      while(Serial.available()) {
        Serial.read();
      }
    }

    if(address < 0x10) Serial.print("00");
    else if(address < 0x100) Serial.print("0");
    Serial.print(address, HEX);
    Serial.print("  ");

    for(int currentByte = 0; currentByte < bytesPerLine; currentByte++) {
      if(address + currentByte < length) {
        byte value = EEPROM.read(address + currentByte);
        if(value < 0x10) Serial.print("0");
        Serial.print(value, HEX);
        Serial.print(" ");
      } else {
        Serial.print(" ");
      }
    }
    Serial.print("  ");

    Serial.print("|");
    for(int currentChar = 0; currentChar < bytesPerLine; currentChar++) {
      if(address + currentChar < length) {
        byte value = EEPROM.read(address + currentChar);
        Serial.print(isPrintable(value) ? (char)value : '.');
      }
    }
    Serial.println("|");
  }
}

void loop() {
  // nothing to see here!
}
