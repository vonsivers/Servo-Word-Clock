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
      #ifdef ESP32
        WiFi.setHostname("ServoWordClock");                   // allow access via http://servowordclock from OUTSIDE network
      #elif defined(ESP8266)
        WiFi.hostname("ServoWordClock");
      #endif
      WiFi.begin(config.ssid.c_str(), config.password.c_str());
      WIFI_connected = WiFi.waitForConnectResult();
      if(WIFI_connected== WL_CONNECTED ) {
        Serial.print("Wifi IP: "); Serial.println(WiFi.localIP());
        // allow access via http://servowordclock.local from INSIDE network
        if (!MDNS.begin("ServoWordClock")) {
          Serial.println("Error setting up MDNS responder!");
        }
        else {
          Serial.println("mDNS responder started");
        }
      }
      else {
        Serial.println("Connection Failed! activating the AP mode...");
        startAP();
      }
}

// reconnect to WiFi if connection was lost
//
void reconnectSTA() {
  int wifi_retry = 0;
  while(WiFi.status() != WL_CONNECTED && wifi_retry < 5 ) {
      wifi_retry++;
      Serial.println("WiFi not connected. Try to reconnect");
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_STA);
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
  // Route for root / web page
  server.on("/api/login", api_login);

  // Route for root / web page
  server.on("/api/changepwd", api_changepwd);

  // Route for root / web page
  server.on("/api/timesettings", api_timesettings);

  // Route for root / web page
  server.on("/api/displayeffects", api_displayeffects);

  // Route for root / web page
  server.on("/api/nightmode", api_nightmode);

  // Route for root / web page
  server.on("/api/wifi", api_wifi);

  // Route for root / web page
  server.on("/api/wifisettings", api_wifisettings);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "index.html", "text/html");
  });
  
  // Route to load style.css file
  server.on("/bundle.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "bundle.css", "text/css");
  });

  // Route to 
  server.on("/bundle.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "bundle.js", "application/javascript");
  });

  // Route to
  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "favicon.ico", "image/x-icon");
  });
  
  // Route to 
  server.on("/manifest.json", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "manifest.json", "application/json");
  });

  // Route to 
  server.on("/polyfills.js", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "polyfills.js", "application/javascript");
  });

  // Route to 
  // server.on("precache-manifest.js", HTTP_GET, [](AsyncWebServerRequest *request){   
    // request->send(SPIFFS, "/precache-manifest.js", "application/javascript");
  // });

  // Route to 
 // server.on("sw.js", HTTP_GET, [](AsyncWebServerRequest *request){   
   // request->send(SPIFFS, "sw.js", "application/javascript");
  //});

  // Route to 
  server.on("/assets/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "/assets/favicon.ico", "image/x-icon");
  });
  
  // Route to 
  server.on("/assets/materialIcons.woff2", HTTP_GET, [](AsyncWebServerRequest *request){  
    request->send(LittleFS, "/assets/materialIcons.woff2", "font/woff2");
  });
  
  // Route to 
  server.on("/assets/android-192x192.png", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "/assets/android-192x192.png", "image/png");
  });

  // Route to 
  server.on("/assets/android-512x512.png", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "/assets/android-512x512.png", "image/png");
  });

  // Route to 
  server.on("/assets/apple.png", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "/assets/apple.png", "image/png");
  });

  // Route to 
  server.on("/assets/favicon-16x16.png", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "/assets/favicon-16x16.png", "image/png");
  });

  // Route to 
  server.on("/assets/favicon-32x32.png", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "/assets/favicon-32x32.png", "image/png");
  });

  // Route to 
  server.on("/assets/mstile-150x150.png", HTTP_GET, [](AsyncWebServerRequest *request){   
    request->send(LittleFS, "/assets/mstile-150x150.png", "image/png");
  });

  // Start server
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "http://localhost:8080");   // avoids CORS error when GUI is running on localhost
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials", "true");
  server.onNotFound([](AsyncWebServerRequest *request) {
    if (request->method() == HTTP_OPTIONS) {
      request->send(200);
    } else {
      request->send(404);
    }
  });
  server.begin();
  Serial.println( "HTTP server started" );
}





#endif
