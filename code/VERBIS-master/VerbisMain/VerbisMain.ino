
#define EN_clock //clock language
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include "FastLED.h"
/*
 * * ESP8266 template with phone config web page
 * based on BVB_WebConfig_OTA_V7 from Andreas Spiess https://github.com/SensorsIot/Internet-of-Things-with-ESP8266
 * and ESPBASE from Pedro Albuquerque https://github.com/Pedroalbuquerque/ESPBASE
 */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <Ticker.h>
#include <EEPROM.h>
#include "global.h"
#include "NTP.h"
// Include STYLE and Script "Pages"
#include "Page_Script.js.h"
#include "Page_Style.css.h"
#include "LedMatrix_functions.h"

#ifdef DE_clock
// Include localized hour generation functions
#include "DE/HourStrings_DE.h"
#include "DE/TimeGen_DE.h"
// Include the localized HTML "Pages"
#include "DE/Page_Admin_DE.h"
#include "DE/Page_NTPSettings_DE.h"
#include "DE/Page_Information_DE.h"
#include "DE/Page_NetworkConfiguration_DE.h"
#include "DE/Page_SetTime_DE.h"
#include "DE/Page_DisplaySettings_DE.h"
#endif

#ifdef EN_clock
// Include localized hour generation functions
#include "EN/HourStrings_EN.h"
#include "EN/TimeGen_EN.h"
// Include the localized HTML "Pages"
#include "EN/Page_Admin_EN.h"
#include "EN/Page_NTPSettings_EN.h"
#include "EN/Page_Information_EN.h"
#include "EN/Page_NetworkConfiguration_EN.h"
#include "EN/Page_SetTime_EN.h"
#include "EN/Page_DisplaySettings_EN.h"
#endif

#ifdef RO_clock
// Include localized hour generation functions
#include "RO/HourStrings_RO.h"
#include "RO/TimeGen_RO.h"
// Include the localized HTML "Pages"
#include "RO/Page_Admin_RO.h"
#include "RO/Page_NTPSettings_RO.h"
#include "RO/Page_Information_RO.h"
#include "RO/Page_NetworkConfiguration_RO.h"
#include "RO/Page_SetTime_RO.h"
#include "Ro/Page_DisplaySettings_RO.h"
#endif

#ifdef HU_clock
// Include localized hour generation functions
#include "HU/HourStrings_HU.h"
#include "HU/TimeGen_HU.h"
// Include the localized HTML "Pages"
#include "HU/Page_Admin_HU.h"
#include "HU/Page_NTPSettings_HU.h"
#include "HU/Page_Information_HU.h"
#include "HU/Page_NetworkConfiguration_HU.h"
#include "HU/Page_SetTime_HU.h"
#include "HU/Page_ColorSettings_HU.h"
#endif

extern "C" {
#include "user_interface.h"
}

void setup() {

  Serial.begin(115200);

  //**** Network Config load
  EEPROM.begin(512); // define an EEPROM space of 512Bytes to store data
  CFG_saved = ReadConfig();

  //  Connect to WiFi acess point or start as Acess point
  if (CFG_saved)  //if no configuration yet saved, load defaults
  {
      // Connect the ESP8266 to local WIFI network in Station mode
      Serial.println("Booting");
      //printConfig();
      WiFi.mode(WIFI_STA);
      WiFi.begin(config.ssid.c_str(), config.password.c_str());
      WIFI_connected = WiFi.waitForConnectResult();
      if(WIFI_connected!= WL_CONNECTED )
          Serial.println("Connection Failed! activating the AP mode...");

      Serial.print("Wifi ip:");Serial.println(WiFi.localIP());
  }

  if ( (WIFI_connected!= WL_CONNECTED) or !CFG_saved){
    // DEFAULT CONFIG
    Serial.println("Setting AP mode default parameters");
    config.ssid = "VERBIS-" + String(ESP.getChipId(),HEX);       // SSID of access point
    config.password = "" ;   // password of access point
    config.dhcp = true;
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 100;
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 254;
    config.ntpServerName = "0.ro.pool.ntp.org"; // to be adjusted to PT ntp.ist.utl.pt
    config.Update_Time_Via_NTP_Every =  3;
    config.timeZone = 20;
    config.isDayLightSaving = true;
    config.DeviceName = "VERBIS";
    config.c_e_o = 1;
    config.startColor = "#0000FF";
    config.endColor = "#FFFFFF";
    WiFi.mode(WIFI_AP);
    WiFi.softAP(config.ssid.c_str());
    Serial.print("Wifi ip:");Serial.println(WiFi.softAPIP());
   }

    // Start HTTP Server for configuration
    server.on ( "/", []() {
      Serial.println("admin.html");
      server.send_P ( 200, "text/html", PAGE_AdminMainPage);  // const char top of page
    }  );

    server.on ( "/favicon.ico",   []() {
      Serial.println("favicon.ico");
      server.send( 200, "text/html", "" );
    }  );

        // Network config
        server.on ( "/config.html", send_network_configuration_html );
        // Info Page
        server.on ( "/info.html", []() {
          Serial.println("info.html");
          server.send_P ( 200, "text/html", PAGE_Information );
        }  );
        server.on ( "/ntp.html", send_NTP_configuration_html  );
        server.on ( "/time.html", send_Time_Set_html );
        server.on ( "/display.html", send_display_settings_html  );
        server.on ( "/style.css", []() {
          Serial.println("style.css");
          server.send_P ( 200, "text/plain", PAGE_Style_css );
        } );
        server.on ( "/microajax.js", []() {
          Serial.println("microajax.js");
          server.send_P ( 200, "text/plain", PAGE_microajax_js );
        } );
        server.on ( "/admin/values", send_network_configuration_values_html );
        server.on ( "/admin/connectionstate", send_connection_state_values_html );
        server.on ( "/admin/infovalues", send_information_values_html );
        server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
        server.on ( "/admin/timevalues", send_Time_Set_values_html );
        server.on ( "/admin/displayvalues", send_display_settings_values_html );

    server.onNotFound ( []() {
      Serial.println("Page Not Found");
      server.send ( 400, "text/html", "Page not Found" );
    }  );
    server.begin();
    Serial.println( "HTTP server started" );

    printConfig();

    // start internal time update ISR
    tkSecond.attach(1, ISRsecondTick);

    FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    Serial.println("FastLed Setup done");

    // start internal time update ISR
    tkSecond.attach(1, ISRsecondTick);

}

// the loop function runs over and over again forever
void loop() {
	  server.handleClient();

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
	   //  feed de DOG :)
	   customWatchdog = millis();

	//============================
	  if  (WIFI_connected != WL_CONNECTED and manual_time_set == false) {
		  config.Update_Time_Via_NTP_Every =  0;
		  afisare_led_no_wifi();
	  }
	  else if (ntp_response_ok == false and manual_time_set == false) {
		  config.Update_Time_Via_NTP_Every =  1;
		  afisare_led_no_ntp();
	  }
	  else if (ntp_response_ok == true or manual_time_set == true){
		  delay(1500);
		  flash();
	  }
	  Gen_Time();
	  FastLED.show();
}
