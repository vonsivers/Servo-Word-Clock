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

#ifndef WIFI_FUNCTIONS_H
#define WIFI_FUNCTIONS_H

/*
// captive portal definition
class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    if(request->url() == "/"){
      request->send_P( 200, "text/html", PAGE_AdminMainPage);
    }
    else if(request->url() == "/config.html") {
      request->send_P( 200, "text/html", send_network_configuration_html);
    }
  }
};
*/


// start AP mode
//
void startAP() {
    Serial.println("Starting WiFi in AP mode");
    WiFi.mode(WIFI_AP);
    #ifdef ESP32
    uint64_t macAddress = ESP.getEfuseMac();
    uint64_t macAddressTrunc = macAddress << 40;
    chipID = macAddressTrunc >> 40;
    #elif defined(ESP8266)
    chipID = ESP.getChipId();
    #endif
    String ssid = "ServoWordClock-" + String(chipID,HEX);       // SSID of access point
    WiFi.softAP(ssid.c_str());
    //dnsServer.start(53, "*", WiFi.softAPIP());
    //server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
    Serial.print("Wifi AP IP: "); Serial.println(WiFi.softAPIP());

    // allow access via http://servowordclock.local from inside network
    if (!MDNS.begin("ServoWordClock")) {
        Serial.println("Error setting up MDNS responder!");
    }
    else {
      Serial.println("mDNS responder started");
    }
    
}

// start station mode
//
void startSTA() {
  // Connect the ESP to local WIFI network in Station mode
      //printConfig();
      Serial.println("Starting WiFi in station mode");
      WiFi.mode(WIFI_STA);
      if (!config.dhcp) {
        WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),  IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ) , IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ));
      }
      else {
        //WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
      }
      #ifdef ESP32
        WiFi.setHostname("ServoWordClock");                   // allow access via http://servowordclock from OUTSIDE network
      #elif defined(ESP8266)
        WiFi.hostname("ServoWordClock");
      #endif
      WiFi.begin(config.ssid.c_str(), config.password.c_str());
      WIFI_connected = WiFi.waitForConnectResult();
      if(WIFI_connected== WL_CONNECTED ) {
        Serial.print("Wifi IP: "); Serial.println(WiFi.localIP());
      }
      else {
        Serial.println("Connection Failed! activating the AP mode...");
        startAP();
      }

      

      // allow access via http://servowordclock.local from INSIDE network
      if (!MDNS.begin("ServoWordClock")) {
        Serial.println("Error setting up MDNS responder!");
      }
      else {
        Serial.println("mDNS responder started");
      }
   
    
  
}

// reconnect to WifI if connection was lost
//
void reconnectSTA() {
  int wifi_retry = 0;
  while(WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
      wifi_retry++;
      Serial.println("WiFi not connected. Try to reconnect");
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_STA);
      if (!config.dhcp) {
        WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),  IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ) , IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ));
      }
      else {
        WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
      }
      #ifdef ESP32
        WiFi.setHostname("ServoWordClock");                   // allow access via http://servowordclock from OUTSIDE network
      #elif defined(ESP8266)
        WiFi.hostname("ServoWordClock");
      #endif
      WiFi.begin(config.ssid.c_str(), config.password.c_str());
      delay(500);
  }
  if(wifi_retry >= 5) {
      Serial.println("\nReboot");
      ESP.restart();
  }
  Serial.print("Wifi IP: "); Serial.println(WiFi.localIP());

      // allow access via http://servowordclock.local from INSIDE network
      /*
      if (!MDNS.begin("ServoWordClock",WiFi.localIP())) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
    */
}

// start webserver
//
void startServer() {
  server.on ( "/", [](AsyncWebServerRequest *request) {
      Serial.println("admin.html");
      if(!request->authenticate(http_username, http_password))
        return request->requestAuthentication();
      request->send_P( 200, "text/html", PAGE_AdminMainPage); 
    }  );

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", PAGE_logout);
  });

    server.on ( "/favicon.ico",   [](AsyncWebServerRequest *request) {
      Serial.println("favicon.ico");
      request->send( 200, "text/html", "" );
    }  );

        server.on ( "/config.html", send_network_configuration_html );
        server.on ( "/info.html", [](AsyncWebServerRequest *request) {
          Serial.println("info.html");
          if(!request->authenticate(http_username, http_password))
            return request->requestAuthentication();
          request->send_P ( 200, "text/html", PAGE_Information );
        }  );
        server.on ( "/ntp.html", send_NTP_configuration_html  );
        server.on ( "/time.html", send_Time_Set_html );
        server.on ( "/display.html", send_display_settings_html  );
        server.on ( "/nightmode.html", send_night_mode_html  );
        server.on ( "/advanced.html", send_admin_settings_html  );
        server.on ( "/style.css", [](AsyncWebServerRequest *request) {
          Serial.println("style.css");
          request->send_P( 200, "text/plain", PAGE_Style_css );
        } );
        server.on ( "/microajax.js", [](AsyncWebServerRequest *request) {
          Serial.println("microajax.js");
          request->send_P( 200, "text/plain", PAGE_microajax_js );
        } );
        server.on ( "/admin/values", send_network_configuration_values_html );
        server.on ( "/admin/connectionstate", send_connection_state_values_html );
        server.on ( "/admin/infovalues", send_information_values_html );
        server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
        server.on ( "/admin/timevalues", send_Time_Set_values_html );
        server.on ( "/admin/displayvalues", send_display_settings_values_html );
        server.on ( "/admin/nightmode", send_night_mode_values_html );
        server.on ( "/admin/adminvalues", send_admin_settings_values_html );

        server.on ( "/restart.html", restart_ESP );            // restart ESP when WIFI setting changed

    server.onNotFound ( [](AsyncWebServerRequest *request) {
      Serial.println("Page Not Found");
      request->send( 404, "text/plain", "Page not Found" );
    }  );
  server.begin();
  Serial.println( "HTTP server started" );
}





#endif
