#include <EEPROM.h>

const int bytesPerLine = 16;
const int length = EEPROM.length();

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println("==== EEPROM HEX & ASCII ====");

  for (int base = 0; base < length; base += bytesPerLine) {
    if(base > 0 && base % 256 == 0) {
      Serial.println("Press ENTER to continue...");
      while(!Serial.available()) {
        ;
      }
      while(Serial.available()) {
        Serial.read();
      }
    }

    byte data[bytesPerLine];
    for (int offset = 0; offset < length; offset += 1) {
      data[offset] = EEPROM.read(base + offset);
    }

    // ADDRESS
    char address[8];
    sprintf(address, "%03x  ", base);
    Serial.print(address);

    // HEX
    char line[80];
    for(int currentByte = 0; currentByte < bytesPerLine; currentByte++) {
      sprintf(line, "%02x ", data[currentByte]);
      if(currentByte == 7) sprintf(line, " ");
      Serial.print(line);
    }

    // ACSII
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
