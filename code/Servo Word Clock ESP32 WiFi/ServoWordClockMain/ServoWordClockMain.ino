#define FASTLED_INTERRUPT_RETRY_COUNT 1
#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
//#include <WebServer.h>
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
  EEPROM.begin(520); // define an EEPROM space of 520 Bytes to store data

  // just for testing clear EEPROM before start -> TO BE REMOVED!
  //ClearConfig();
  
  CFG_saved = ReadConfig();

  //  connect to WiFi or start as access point
  if (CFG_saved) {
    startSTA();
  }
  else {
    DefaultConfig();
    startAP();
  }

  // start web server 
  startServer();

  printConfig();

  pwm1.begin();
  pwm1.setPWMFreq(120);  
  pwm2.begin();
  pwm2.setPWMFreq(120);  
  pwm3.begin();
  pwm3.setPWMFreq(120);  
  pwm4.begin();
  pwm4.setPWMFreq(120);  
  pwm5.begin();
  pwm5.setPWMFreq(120);  
  pwm6.begin();
  pwm6.setPWMFreq(120);  
  pwm7.begin();
  pwm7.setPWMFreq(120);  
  pwm8.begin();
  pwm8.setPWMFreq(120);
  pwm9.begin();
  pwm9.setPWMFreq(120);
  pwm10.begin();
  pwm10.setPWMFreq(120);
  pwm11.begin();
  pwm11.setPWMFreq(120); 

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
