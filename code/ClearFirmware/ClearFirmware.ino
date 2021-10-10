#include <LittleFS.h>
#include <EEPROM.h>

void setup() {
  // define an EEPROM space of 512 Bytes to store data
  EEPROM.begin(512);

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  // delete all files in SPIFF and littleFS
    bool formatted1 = SPIFFS.format();
    bool formatted = LittleFS.format();

    if(formatted && formatted1){
    Serial.println("\n\nSuccess formatting");
  }else{
    Serial.println("\n\nError formatting");
  }

  // clear EEPROM
  for (int i = 0 ; i < 512 ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();

}

void loop() {
}
