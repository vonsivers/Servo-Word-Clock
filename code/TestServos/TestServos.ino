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
#include <ArduinoOTA.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// min/max position of servos
const uint16_t SERVOMIN = 400;
const uint16_t SERVOMAX = 700;

// delay (ms) between servo position update when moving slow/fast
uint16_t DELAY_slow = 5;   
uint16_t DELAY_fast = 1;

// setup servo drivers
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(&Wire, 0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(&Wire, 0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(&Wire, 0x42);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(&Wire, 0x43);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(&Wire, 0x44);
Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver(&Wire, 0x45);
Adafruit_PWMServoDriver pwm7 = Adafruit_PWMServoDriver(&Wire, 0x46);
Adafruit_PWMServoDriver pwm8 = Adafruit_PWMServoDriver(&Wire, 0x47);
Adafruit_PWMServoDriver pwm9 = Adafruit_PWMServoDriver(&Wire, 0x48);
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(&Wire, 0x49);
Adafruit_PWMServoDriver pwm11 = Adafruit_PWMServoDriver(&Wire, 0x4A);

// start AP mode
//
void startAP() {
    Serial.println("Starting WiFi in AP mode");
    WiFi.mode(WIFI_AP);
    String ssid = "ServoWordClock-" + String(ESP.getChipId(),HEX);       // SSID of access point
    WiFi.softAP(ssid.c_str());
    Serial.print("Wifi AP IP: "); Serial.println(WiFi.softAPIP());
    
}

// initialize servos
//
void initServos() {
  
  pwm1.begin();
  pwm1.setPWMFreq(120);
  delay(100);  
  pwm2.begin();
  pwm2.setPWMFreq(120);
  delay(100);   
  pwm3.begin();
  pwm3.setPWMFreq(120);
  delay(100);   
  pwm4.begin();
  pwm4.setPWMFreq(120);
  delay(100);   
  pwm5.begin();
  pwm5.setPWMFreq(120);
  delay(100);   
  pwm6.begin();
  pwm6.setPWMFreq(120); 
  delay(100);  
  pwm7.begin();
  pwm7.setPWMFreq(120);
  delay(100);   
  pwm8.begin();
  pwm8.setPWMFreq(120);
  delay(100); 
  pwm9.begin();
  pwm9.setPWMFreq(120);
  delay(100); 
  pwm10.begin();
  pwm10.setPWMFreq(120);
  delay(100); 
  pwm11.begin();
  pwm11.setPWMFreq(120);

}

// move servo to position
//
void moveServo(int row, int column, unsigned int pos) {

    // check if position is within limits
    if (pos<=SERVOMAX && pos>=SERVOMIN) {

      if(row<10) {
      switch(column) {
        case 0: pwm11.setPWM(row,0,pos); break;
        case 1: pwm10.setPWM(row,0,pos); break;
        case 2: pwm9.setPWM(row,0,pos); break;
        case 3: pwm8.setPWM(row,0,pos); break;
        case 4: pwm7.setPWM(row,0,pos); break;
        case 5: pwm6.setPWM(row,0,pos); break;
        case 6: pwm5.setPWM(row,0,pos); break;
        case 7: pwm4.setPWM(row,0,pos); break;
        case 8: pwm3.setPWM(row,0,pos); break;
        case 9: pwm2.setPWM(row,0,pos); break;
        case 10: pwm1.setPWM(row,0,pos); break;
      }
      }
      else {
        switch(column) {
        case 0: pwm7.setPWM(15,0,pos); break;
        case 1: pwm6.setPWM(15,0,pos); break;
        case 2: pwm5.setPWM(15,0,pos); break;
        case 3: pwm4.setPWM(15,0,pos); break;
      }
    }
  }
}

// move all servos to back fast
//
void zeroServos() {
  for (int row=0; row<11; row++) {
    for (int column=0; column<11; column++) {
      moveServo(row,column,SERVOMIN);
      delay(1000);
    }
  }
}

// move all servos slowly to front one after the other
//
void ServosToFront() {
  for (int row=0; row<11; ++row) {
    for (int column=0; column<11; ++column) {
      for(int pos=SERVOMIN+1; pos<=SERVOMAX; pos++) {
        moveServo(row,column,pos);
        delay(DELAY_slow);
      } 
    }
  }
}

// move all servos slowly to back one after the other
//
void ServosToBack() {
  for (int row=0; row<11; ++row) {
    for (int column=0; column<11; ++column) {
      for(int pos=SERVOMAX-1; pos>=SERVOMIN; pos--) {
        moveServo(row,column,pos);
        delay(DELAY_slow);
      } 
    }
  }
}

 
void setup(){

  
  // Serial port for debugging purposes
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Booting"); 

  // start access point
  startAP();

  // OTA configuration
  String hname = "ServoWordClock-" + String(ESP.getChipId(),HEX);
  ArduinoOTA.setHostname(hname.c_str());
  
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

  Serial.println("Setup done");
}
 
void loop(){
  
  ArduinoOTA.handle();

  // move all servos to back fast
  zeroServos();

  delay(3000);

  // move servos to front slow
  ServosToFront();

  delay(3000);

  // move servos to back slow
  ServosToBack();

  delay(3000);
  
}
