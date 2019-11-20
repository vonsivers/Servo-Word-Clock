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
  // DEFAULT CONFIG
    Serial.println("Starting WiFi in AP mode");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(config.ssid.c_str());
    //dnsServer.start(53, "*", WiFi.softAPIP());
    //server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
    Serial.print("Wifi ip:");Serial.println(WiFi.softAPIP());

    // allow access via http://servowordclock.local from inside network
    if (!MDNS.begin("ServoWordClock")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
}

// start station mode
//
void startSTA() {
  // Connect the ESP to local WIFI network in Station mode
      //printConfig();
      Serial.println("Starting WiFi in station mode");
      WiFi.mode(WIFI_STA);
      WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
      WiFi.setHostname("ServoWordClock");                   // allow access via http://servowordclock from OUTSIDE network
      WiFi.begin(config.ssid.c_str(), config.password.c_str());
      WIFI_connected = WiFi.waitForConnectResult();
      if(WIFI_connected!= WL_CONNECTED ) {
          Serial.println("Connection Failed! activating the AP mode...");
          startAP();
      }

      Serial.print("Wifi ip:");Serial.println(WiFi.localIP());

      // allow access via http://servowordclock.local from INSIDE network
      if (!MDNS.begin("ServoWordClock")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
  
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
      WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
      WiFi.setHostname("ServoWordClock");                   // allow access via http://servowordclock from OUTSIDE network
      WiFi.begin(config.ssid.c_str(), config.password.c_str());
      delay(500);
  }
  if(wifi_retry >= 5) {
      Serial.println("\nReboot");
      ESP.restart();
  }
  Serial.print("Wifi ip:");Serial.println(WiFi.localIP());

      // allow access via http://servowordclock.local from INSIDE network
      if (!MDNS.begin("ServoWordClock")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
}

// start webserver
//
void startServer() {
  server.on ( "/", [](AsyncWebServerRequest *request) {
      Serial.println("admin.html");
      //server.send_P ( 200, "text/html", PAGE_AdminMainPage);  // const char top of page
      request->send_P( 200, "text/html", PAGE_AdminMainPage); 
    }  );

    server.on ( "/favicon.ico",   [](AsyncWebServerRequest *request) {
      Serial.println("favicon.ico");
      //server.send( 200, "text/html", "" );
      request->send( 200, "text/html", "" );
    }  );

        server.on ( "/config.html", send_network_configuration_html );
        server.on ( "/ntp.html", send_NTP_configuration_html  );
        server.on ( "/time.html", send_Time_Set_html );
        server.on ( "/display.html", send_display_settings_html  );
        server.on ( "/nightmode.html", send_night_mode_html  );
        server.on ( "/style.css", [](AsyncWebServerRequest *request) {
          Serial.println("style.css");
          //server.send_P ( 200, "text/plain", PAGE_Style_css );
          request->send_P( 200, "text/plain", PAGE_Style_css );
        } );
        server.on ( "/microajax.js", [](AsyncWebServerRequest *request) {
          Serial.println("microajax.js");
          //server.send_P ( 200, "text/plain", PAGE_microajax_js );
          request->send_P( 200, "text/plain", PAGE_microajax_js );
        } );
        server.on ( "/admin/values", send_network_configuration_values_html );
        server.on ( "/admin/connectionstate", send_connection_state_values_html );
        server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
        server.on ( "/admin/timevalues", send_Time_Set_values_html );
        server.on ( "/admin/displayvalues", send_display_settings_values_html );
        server.on ( "/admin/nightmode", send_night_mode_values_html );

    server.onNotFound ( [](AsyncWebServerRequest *request) {
      Serial.println("Page Not Found");
      //server.send ( 400, "text/html", "Page not Found" );
      request->send( 404, "text/plain", "Page not Found" );
    }  );
  server.begin();
  Serial.println( "HTTP server started" );
}


// configure Wifi
//
/*
void ConfigureWifi(){
  Serial.println("Configuring Wifi");
  WiFi.begin (config.ssid.c_str(), config.password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    delay(500);
  }
  if (!config.dhcp)
  {
    WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),  IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ) , IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ));
  }
}
*/

#endif
