/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
//#include <FS.h>
#include <LittleFS.h>
#include <TimeLib.h>
#include <EEPROM.h>
#include <Ticker.h>

#include "global.h"
#include "api_login.h"
#include "api_timesettings.h"
#include "api_nightmode.h"
#include "api_displayeffects.h"
#include "api_wifi.h"
#include "api_wifisettings.h"
#include "api_changepwd.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

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
  // Serial port for debugging purposes
  Serial.begin(115200);

  // define an EEPROM space of 512 Bytes to store data
  EEPROM.begin(512); 

  randomSeed(analogRead(0));    // Seed RNG

  delay(1000);

  // just for testing clear EEPROM before start -> TO BE REMOVED!
 ClearConfig();

 DefaultConfig();

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
  

  // Connect to Wi-Fi
  WiFi.begin(config.ssid, config.password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

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
}
 
void loop(){
  
}
