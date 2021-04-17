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
    
    Copyright 2021, Moritz v. Sivers
 */

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>    // https://github.com/me-no-dev/ESPAsyncWebServer
//#include <WiFiUdp.h>
#include <LittleFS.h>
//#include <TimeLib.h>                https://github.com/PaulStoffregen/Time (for manual timesetting via setTime())
#include <time.h>                   // time() ctime()
#include <coredecls.h>              // settimeofday_cb()
#include <sys/time.h>                   // struct timeval
#include <sntp.h>                       // sntp_servermode_dhcp()
#include <TZ.h>                     // https://raw.githubusercontent.com/nayarsystems/posix_tz_db/master/zones.csv
#include <EEPROM.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// MCU functions
#include "global.h"
#include "NTP.h"
#include "LedMatrix_functions.h"
#include "TimeGen.h"

// api functions
#include "api_login.h"
#include "api_timesettings.h"
#include "api_nightmode.h"
#include "api_displayeffects.h"
#include "api_wifi.h"
#include "api_wifisettings.h"
#include "api_changepwd.h"

#include "WiFi_functions.h" // needs to come after api_wifi.h

// list all files in SPIFF -> TO BE REMOVED
void listAllFiles(){
  //Dir dir = SPIFFS.openDir ("");
  Dir dir = LittleFS.openDir ("/");
  while (dir.next ()) {
    Serial.println (dir.fileName ());
    Serial.println (dir.fileSize ());
  }
  dir = LittleFS.openDir ("/assets");
  while (dir.next ()) {
    Serial.println (dir.fileName ());
    Serial.println (dir.fileSize ());
  }
 
}
 
void setup(){

  // clear LEDs directly after start
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();

  // Serial port for debugging purposes
  Serial.begin(115200);
  
  Serial.println("Booting");

  randomSeed(analogRead(0));    // Seed RNG
 // create random login key
 loginkey = createRandString();

  // Initialize SPIFFS
  //if(!SPIFFS.begin()){
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

// delete all files in SPIFF -> TO BE REMOVED
/*
    //bool formatted = SPIFFS.format();
    bool formatted = LittleFS.format();

    if(formatted){
    Serial.println("\n\nSuccess formatting");
  }else{
    Serial.println("\n\nError formatting");
  }
*/

  Serial.println("\n\n----Listing files----");
  listAllFiles();

  // define an EEPROM space of 512 Bytes to store data
  EEPROM.begin(512); 
  
  // just for testing clear EEPROM before start -> TO BE REMOVED!
  //ClearConfig();
  
  CFG_saved = ReadConfig();

  //  connect to WiFi or start as access point
  if (CFG_saved) {
    startSTA();
  }
  else {
    DefaultConfig();
    WriteConfig();
    startAP();
  }
  printConfig();

  // start web server 
  startServer();

  // OTA configuration
  String hname = "ServoWordClock-" + String(ESP.getChipId(),HEX);
  ArduinoOTA.setHostname(hname.c_str());
  ArduinoOTA.setPassword((const char *)"ServoWordClockOTA");
  
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  // initialize servo controller boards
  initServos(); 

  // only reset servos if clock is in normal mode
  currentMode = config.clockmode;    
  if(currentMode == 0) {
    initMatrix();
  }
  // otherwise put servos again to sleep
  else {
    sleepServos();
  }
  // initialize servo position variables
  initCurrentPos();
  
  lastmin = tm.tm_min; // initialize last update of display
 
  // start internal time update ISR
  tkSecond.attach(1, ISRsecondTick);

  // install callback - called when settimeofday is called (by SNTP or user)
  // once enabled (by DHCP), SNTP is updated every hour by default
  // ** optional boolean in callback function is true when triggerred by SNTP **
  settimeofday_cb(time_is_set);

  // configure NTP
  initNTP();

  // Give now a chance to the settimeofday callback,
  // because it is *always* deferred to the next yield()/loop()-call.
  yield();

  Serial.println("Setup done");
}
 
void loop(){
  ArduinoOTA.handle();

  if  (WIFI_connected != WL_CONNECTED and time_was_set == false) {
    LED_no_wifi();
    ntpAnimation = false;
  }
  else if (WIFI_connected == WL_CONNECTED and time_was_set == false) {
    LED_no_ntp();
  }
  else if (time_was_set){
    Gen_Time();
    // if wifi connection got lost attempt reconnect
    if (WIFI_connected == WL_CONNECTED and WiFi.status() != WL_CONNECTED) {
      reconnectSTA();
      startServer();
    }
    ntpAnimation = false;
  }
}
