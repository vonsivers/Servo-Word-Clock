/*
    This file is part of Servo Wordclock.

    Servo Wordclock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Servo Wordclock is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Servo Wordclock.  If not, see <https://www.gnu.org/licenses/>.
    
    Copyright 2021 Moritz v. Sivers
 */

#ifndef GLOBAL_H
#define GLOBAL_H

DNSServer dnsServer;
AsyncWebServer server(80);

int WIFI_connected = false;
bool time_was_set = false;
bool CFG_saved = false;
Ticker tkSecond;												  // Second - Timer for Updating tm Structure
time_t now;                               // this is the epoch
tm tm;                                    // the structure tm holds time information in a more convient way
String loginkey;                          // random login key
long logintimestamp;                      // time of last correct login
uint8_t lastmin;                          // minute of last display update
bool updateDisplay = false;               // set to true if display needs update
static Ticker deferred;       // needed to delay ESP restart in api_wifi.h

// ESP chip ID
#ifdef ESP32
  uint64_t macAddress = ESP.getEfuseMac();
  uint64_t macAddressTrunc = macAddress << 40;
  uint32_t chipID = macAddressTrunc >> 40;
#elif defined(ESP8266)
  uint32_t chipID = ESP.getChipId();
#endif

struct strConfig {
  String timeMode;                      // up to 32 Byte - EEPROM 17 
  uint8_t timeZone;                     // 1 Byte - EEPROM 49
  String ssid;                          // up to 32 Byte - EEPROM 50
  String password;                      // up to 32 Byte - EEPROM 82
  String wcolor;                        // up to 32 Byte - EEPROM 114
  String bcolor;                        // up to 32 Byte - EEPROM 146
  String dcolor;                        // up to 32 Byte - EEPROM 178
  uint8_t dcolormode;                   // 1 Byte - EEPROM 210
  uint8_t wcolormode;                   // 1 Byte - EEPROM 211
  uint8_t bcolormode;                   // 1 Byte - EEPROM 212
  uint8_t brightness;                   // 1 Byte - EEPROM 213
  uint8_t meffect;                      // 1 Byte - EEPROM 214
  uint8_t heffect;                      // 1 Byte - EEPROM 215  
  uint8_t clockmode;                    // 1 Byte - EEPROM 216
  uint8_t nightmode;                    // 1 Byte - EEPROM 217
  uint8_t wd_hour_start;                // 1 Byte - EEPROM 218
  uint8_t wd_minute_start;              // 1 Byte - EEPROM 219
  uint8_t wd_hour_end;                  // 1 Byte - EEPROM 220
  uint8_t wd_minute_end;                // 1 Byte - EEPROM 221
  uint8_t we_hour_start;                // 1 Byte - EEPROM 222
  uint8_t we_minute_start;              // 1 Byte - EEPROM 223
  uint8_t we_hour_end;                  // 1 Byte - EEPROM 224
  uint8_t we_minute_end;                // 1 Byte - EEPROM 225
  String login;                         // up to 32 Byte - EEPROM 226
} config;


// create random string for login
String createRandString() {
  
  byte randomValue;
  char msg[32];     // Keep in mind SRAM limits
  int numBytes = 32;
 
  //memset(msg, 0, sizeof(msg));
  for(int i = 0; i < numBytes-1; i++) {
    randomValue = random(0, 36);
    if(randomValue < 10){
      msg[i] = randomValue + '0';
    }else{
      msg[i] = (randomValue - 10) + 'a';
    }
  }
  msg[numBytes-1] = '\0';  // add termination character
  String str(msg);
  Serial.println("Here is your random string: ");
  Serial.println(str); 
  return str;
}

// returns false if nonew login in the last 10 minutes
bool checkLogin(String key) {
  if(key==loginkey) {
    if((millis()-logintimestamp)<10*60*1000) {
      logintimestamp = millis();
      return true;
    }
  }
  return false;
}

//  Auxiliar function to handle EEPROM

void EEPROMWritelong(int address, long value){
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

// Check the Values is between 0-255
boolean checkRange(String Value){
  if (Value.toInt() < 0 || Value.toInt() > 255)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void WriteStringToEEPROM(int beginaddress, String string){
  char  charBuf[string.length() + 1];
  string.toCharArray(charBuf, string.length() + 1);
  for (int t =  0; t < sizeof(charBuf); t++)
  {
    EEPROM.write(beginaddress + t, charBuf[t]);
  }
}

String  ReadStringFromEEPROM(int beginaddress){
  volatile byte counter = 0;
  char rChar;
  String retString = "";
  while (1)
  {
    rChar = EEPROM.read(beginaddress + counter);
    if (rChar == 0) break;
    if (counter > 31) break;
    counter++;
    retString.concat(rChar);

  }
  return retString;
}


void DefaultConfig() { 
    config.timeMode = "internet";   
    config.timeZone = 0;
    config.ssid = "ServoWordClock-" + String(chipID,HEX);       
    config.password = "";
    config.wcolor = "#ff0000";
    config.bcolor = "#ff0000";
    config.dcolor = "#ff0000";
    config.dcolormode = 0;
    config.wcolormode = 0;
    config.bcolormode = 0;
    config.brightness = 150;
    config.meffect = 0;
    config.heffect = 0;
    config.clockmode = 0;
    config.nightmode = 0;
    config.wd_hour_start = 0;
    config.wd_minute_start = 0;
    config.wd_hour_end = 0;
    config.wd_minute_end = 0;
    config.we_hour_start = 0;
    config.we_minute_start = 0;
    config.we_hour_end = 0;
    config.we_minute_end = 0;
    config.login = "114servos";
}

void WriteConfig(){

  Serial.println("Writing Config ...");
  EEPROM.write(0, 'C');
  EEPROM.write(1, 'F');
  EEPROM.write(2, 'G');

  WriteStringToEEPROM(17, config.timeMode);
  EEPROM.write(49, config.timeZone); 
  WriteStringToEEPROM(50, config.ssid);
  WriteStringToEEPROM(82, config.password);
  WriteStringToEEPROM(114, config.wcolor);
  WriteStringToEEPROM(146, config.bcolor);
  WriteStringToEEPROM(178, config.dcolor);
  EEPROM.write(210, config.dcolormode);
  EEPROM.write(211, config.wcolormode);
  EEPROM.write(212, config.bcolormode);
  EEPROM.write(213, config.brightness);
  EEPROM.write(214, config.meffect);
  EEPROM.write(215, config.heffect);
  EEPROM.write(216, config.clockmode);
  EEPROM.write(217, config.nightmode);
  EEPROM.write(218, config.wd_hour_start);
  EEPROM.write(219, config.wd_minute_start);
  EEPROM.write(220, config.wd_hour_end);
  EEPROM.write(221, config.wd_minute_end);
  EEPROM.write(222, config.we_hour_start);
  EEPROM.write(223, config.we_minute_start);
  EEPROM.write(224, config.we_hour_end);
  EEPROM.write(225, config.we_minute_end);
  WriteStringToEEPROM(226, config.login);
  
  EEPROM.commit();
  Serial.println("Config Saved!");
}

void ClearConfig() {
  for (int i = 0 ; i < 512 ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

boolean ReadConfig(){
  Serial.println("Reading Configuration");
  if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
  {
    Serial.println("Configuration Found!");
    config.timeMode = ReadStringFromEEPROM(17);
    config.timeZone = EEPROM.read(49);
    config.ssid = ReadStringFromEEPROM(50);
    config.password = ReadStringFromEEPROM(82);
    config.wcolor = ReadStringFromEEPROM(114);
    config.bcolor = ReadStringFromEEPROM(146);
    config.dcolor = ReadStringFromEEPROM(178);
    config.dcolormode = EEPROM.read(210);
    config.wcolormode = EEPROM.read(211);
    config.bcolormode = EEPROM.read(212);
    config.brightness = EEPROM.read(213);
    config.meffect = EEPROM.read(214);
    config.heffect = EEPROM.read(215);
    config.clockmode = EEPROM.read(216);
    config.nightmode = EEPROM.read(217);
    config.wd_hour_start = EEPROM.read(218);
    config.wd_minute_start = EEPROM.read(219);
    config.wd_hour_end = EEPROM.read(220);
    config.wd_minute_end = EEPROM.read(221);
    config.we_hour_start = EEPROM.read(222);
    config.we_minute_start = EEPROM.read(223);
    config.we_hour_end = EEPROM.read(224);
    config.we_minute_end = EEPROM.read(225);
    config.login = ReadStringFromEEPROM(226);
    
    return true;

  }
  else
  {
    Serial.println("Configuration NOT FOUND!!!!");
    return false;
  }
}


void printConfig(){

  Serial.println("Printing Config");
  Serial.println("------------------");
  Serial.printf("Timemode:%s\n", config.timeMode.c_str());
  Serial.printf("Timezone %d\n", config.timeZone); 
  Serial.printf("SSID:%s\n", config.ssid.c_str());
  Serial.printf("PWD:%s\n", config.password.c_str());
  Serial.printf("Dot Color:%s\n", config.dcolor.c_str());
  Serial.printf("Word Color:%s\n", config.wcolor.c_str());
  Serial.printf("Background Color:%s\n", config.bcolor.c_str());
  Serial.printf("Dot Color Mode:%d\n", config.dcolormode);
  Serial.printf("Word Color Mode:%d\n", config.wcolormode);
  Serial.printf("Bkg Color Mode:%d\n", config.bcolormode);
  Serial.printf("Brightness %d\n", config.brightness); 
  Serial.printf("Minute Effect:%d\n", config.meffect);
  Serial.printf("Hour Effect:%d\n", config.heffect);
  Serial.printf("Clock Mode:%d\n", config.clockmode);
  Serial.printf("Night Mode:%d\n", config.nightmode);
  Serial.printf("weekdays hour start: %d\n", config.wd_hour_start);
  Serial.printf("weekdays minute start: %d\n", config.wd_minute_start);
  Serial.printf("weekdays hour end: %d\n", config.wd_hour_end);
  Serial.printf("weekdays minute end: %d\n", config.wd_minute_end);
  Serial.printf("weekend hour start: %d\n", config.we_hour_start);
  Serial.printf("weekend minute start: %d\n", config.we_minute_start);
  Serial.printf("weekend hour end: %d\n", config.we_hour_end);
  Serial.printf("weekend minute end: %d\n", config.we_minute_end);
  Serial.println("------------------");

}


#endif
