#ifndef API_TIMESETTINGS_H
#define API_TIMESETTINGS_H


void api_timesettings_post(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__);
  
  config.timeMode = request->getParam("mode",true)->value();
  config.timeZone = request->getParam("timezone",true)->value().toInt();
  config.isDayLightSaving = request->getParam("use_dst",true)->value().toInt() == 1;
  String manual_time = request->getParam("manual_time",true)->value();

  // parse string "hh:mm"
  int Hour, Minute, Second ;
  sscanf(manual_time.c_str(), "%d:%d", &Hour, &Minute);

  // set custom time
  if(config.timeMode == "custom") {
    setTimeUser(Hour,Minute,0,1,1,2000);
  }
  else {  // configure NTP timezone
    initNTP();
  }

  Serial.println(config.timeMode);
  Serial.println(config.timeZone);
  Serial.println(config.isDayLightSaving);
  Serial.println(manual_time);
  
  WriteConfig();

  request->send(200);
}


void api_timesettings_get(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__); 

  String result = "";
   result += "mode\n" + (String) config.timeMode + "\n\n";
   result += "timezone\n" + (String) config.timeZone + "\n\n";
   result += "use_dst\n" + (String) config.isDayLightSaving + "\n\n";
   result += "manual_time\n" + (String) tm.tm_hour + ":" + (String) tm.tm_min;

    Serial.println(result);
  
    request->send ( 200, "text/plain", result );

  
}



void api_timesettings(AsyncWebServerRequest *request)
{
    if(
      (request->hasParam("key") && checkLogin(request->getParam("key")->value())) ||
      (request->hasParam("key",true) && checkLogin(request->getParam("key", true)->value()))
    ){
      if(request->method() == HTTP_POST) {
        api_timesettings_post(request);
      }
      else {
        api_timesettings_get(request);
      }
   }
    else{
      request->send (403,"text/plain", "Access Denied!");
    }
}



  
#endif
