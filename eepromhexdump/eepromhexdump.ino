#include <EEPROM.h>

const int bytesPerLine = 16;
const int length = EEPROM.length();

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println("==== EEPROM HEX & ASCII ====");

  for (int addr = 0; addr < length; addr += bytesPerLine) {
    byte data[bytesPerLine];
    for (int offset = 0; offset < length; offset += 1) {
      data[offset] = EEPROM.read(addr + offset);
    }

    char address[8];
    sprintf(address, "%03x  ", addr);
    Serial.print(address);

    char line[80];
    for(int currentByte = 0; currentByte < bytesPerLine; currentByte++) {
      sprintf(line, "%02x ", data[currentByte]);
      if(currentByte == 7) sprintf(line, " ");
      Serial.print(line);
    }

    Serial.print(" |");
    for(int currentByte = 0; currentByte < bytesPerLine; currentByte++) {
      char c = data[currentByte];
      if(c >= 32 && c <=126) {
        Serial.print(c);
      } else {
        Serial.print('.');
      }
    }
    Serial.println("|");
  }
}

void loop() {
  // Nothing here
}

