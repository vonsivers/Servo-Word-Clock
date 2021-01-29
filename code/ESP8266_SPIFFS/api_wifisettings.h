#ifndef API_WIFISETTINGS_H
#define API_WIFISETTINGS_H


void api_wifisettings_get(AsyncWebServerRequest *request) {
  
	Serial.println(__FUNCTION__);

  String result = "";

  // trigger Wi-Fi network scan
  Serial.println("start WiFi scan ...");
  int n = WiFi.scanComplete();
  if(n == -2){
    WiFi.scanNetworks(true);
  } else if(n){
    for (int i = 0; i < n; ++i)
    {
      int quality=0;
      if(WiFi.RSSI(i) <= -100)
      {
          quality = 0;
      }
      else if(WiFi.RSSI(i) >= -50)
      {
          quality = 100;
      }
      else
      {
        quality = 2 * (WiFi.RSSI(i) + 100);
      }

    #ifdef ESP32
      result += String(WiFi.SSID(i))  + "\n" +  String(quality) + "\n" +  String((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"0":"1")  + "\n\n";
    #elif defined(ESP8266)
      result += String(WiFi.SSID(i))  + "\n" +  String(quality) + "\n" +  String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?"0":"1")  + "\n\n";
    #endif
    }
    WiFi.scanDelete();
    if(WiFi.scanComplete() == -2){
      WiFi.scanNetworks(true);
    }
  }
    Serial.println(result);

  /*
  int n =  WiFi.scanNetworks();
  Serial.println(n);
  if (n>0) {
    Serial.println("some networks found ");
    for (int i = 0; i < n; ++i)
    {
      int quality=0;
      if(WiFi.RSSI(i) <= -100)
      {
          quality = 0;
      }
      else if(WiFi.RSSI(i) >= -50)
      {
          quality = 100;
      }
      else
      {
        quality = 2 * (WiFi.RSSI(i) + 100);
      }

    #ifdef ESP32
      result += String(WiFi.SSID(i))  + "\n" +  String(quality) + "\n" +  String((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"0":"1")  + "\n\n";
    #elif defined(ESP8266)
      result += String(WiFi.SSID(i))  + "\n" +  String(quality) + "\n" +  String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?"0":"1")  + "\n\n";
    #endif
    Serial.println(result);
    }
  }
  */

  request->send ( 200, "text/plain", result );

}



void api_wifisettings(AsyncWebServerRequest *request)
{
    if(
      (request->hasParam("key") && checkLogin(request->getParam("key")->value())) ||
      (request->hasParam("key",true) && checkLogin(request->getParam("key", true)->value()))
    ){
      if(request->method() == HTTP_GET) {
      api_wifisettings_get(request);
  	}
  }
  else{
    request->send (403,"text/plain", "Access Denied!");
  }
        
}


  
#endif
