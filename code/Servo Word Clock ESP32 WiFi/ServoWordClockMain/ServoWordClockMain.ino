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
 
    based on VERBIS by Andrei Erdei - https://github.com/ancalex/VERBIS
    modifed by Moritz v. Sivers, 25.11.2019
    
    Copyright 2019 Moritz v. Sivers
 */

#define FASTLED_INTERRUPT_RETRY_COUNT 1
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <DNSServer.h>
#include "ESPAsyncWebServer.h"    // https://github.com/me-no-dev/ESPAsyncWebServer
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <Ticker.h>
#include <EEPROM.h>

// global variables
#include "global.h"

// functions
#include "NTP.h"
#include "LedMatrix_functions.h"
#include "TimeGen.h"

// STYLE and Script "Pages"
#include "Page_Script.js.h"
#include "Page_Style.css.h"

// HTML "Pages"
#include "Page_Admin.h"
#include "Page_NTPSettings.h"
#include "Page_NetworkConfiguration.h"
#include "Page_SetTime.h"
#include "Page_DisplaySettings.h"
#include "Page_NightMode.h"
#include "Page_Information.h"
#include "Page_AdminSettings.h"

#include "WiFi_functions.h"

//extern "C" {
//#include "user_interface.h"
//}

void setup() {

  // clear LEDs directly after start
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
  
  Serial.begin(115200);

  Serial.println("Booting");

  // get random seed from unused pin
  randomSeed(analogRead(2));

  //**** Network Config load
  EEPROM.begin(512); // define an EEPROM space of 512 Bytes to store data

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

  // start web server 
  startServer();

  printConfig();

  initServos(); 

  currentMode = config.clockmode;    // get current clock mode first: no resetting of servos if clockmode is silent
  initMatrix();

  lastmin = DateTime.minute; // initialize last update of display
 
  // start internal time update ISR
  tkSecond.attach(1, ISRsecondTick);

  Serial.println("Setup done");
}


void loop() {
  //dnsServer.processNextRequest();
	  //server.handleClient();

	  if (config.Update_Time_Via_NTP_Every  > 0 )
	  {
	    if (cNTP_Update > 5 && firstStart)
	    {
	      getNTPtime();
	      cNTP_Update =0;
	      firstStart = false;
        updateDisplay = true;
        //FastLED.clear();
	    }
	    else if ( cNTP_Update > (config.Update_Time_Via_NTP_Every * 60) )
	    {
	      getNTPtime();
	      cNTP_Update =0;
	    }
	  }
	   //  feed the DOG :)
	   //customWatchdog = millis();

	//============================
	  if  (WIFI_connected != WL_CONNECTED and manual_time_set == false) {
		  config.Update_Time_Via_NTP_Every =  0;
		  LED_no_wifi();
	  }
	  else if (ntp_response_ok == false and manual_time_set == false) {
		  config.Update_Time_Via_NTP_Every =  1;
		  LED_no_ntp();
	  }
	  else if (ntp_response_ok == true or manual_time_set == true){
		  Gen_Time();
      // if wifi connection got lost attempt reconnect
      if ( ntp_response_ok == true and WiFi.status() != WL_CONNECTED) {
        reconnectSTA();
        startServer();
      }
	  }
	  
}
