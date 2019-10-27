#define FASTLED_INTERRUPT_RETRY_COUNT 0
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

#include "WiFi_functions.h"

//extern "C" {
//#include "user_interface.h"
//}

void setup() {
  Serial.begin(115200);

  Serial.println("Booting");

  //**** Network Config load
  EEPROM.begin(512); // define an EEPROM space of 512Bytes to store data

  // just for testing clear EEPROM before start -> TO BE REMOVED!
  //ClearConfig();
  
  CFG_saved = ReadConfig();

  //  connect to WiFi or start as access point
  if (CFG_saved) {
    startSTA();
  }
  else {
    startAP();
  }

  // start web server 
  startServer();

  printConfig();

  // start internal time update ISR
  tkSecond.attach(1, ISRsecondTick);

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

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

  initMatrix();

  delay(1000);

  lastmin = DateTime.minute; // initialize last update of display

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
	    }
	    else if ( cNTP_Update > (config.Update_Time_Via_NTP_Every * 60) )
	    {
	      getNTPtime();
	      cNTP_Update =0;
	    }
	  }
	   //  feed the DOG :)
	   customWatchdog = millis();

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
	  }
	  
}
