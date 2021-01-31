#ifndef API_NIGHTMODE_H
#define API_NIGHTMODE_H


void api_nightmode_post(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__);
  
  config.nightmode = request->getParam("mode",true)->value().toInt();
  String weekday_start = request->getParam("weekday_start",true)->value();
  String weekday_end = request->getParam("weekday_end",true)->value();
  String weekend_start = request->getParam("weekend_start",true)->value();
  String weekend_end = request->getParam("weekend_end",true)->value();

  // parse string "hh:mm"
  int Hour, Minute;
  sscanf(weekday_start.c_str(), "%d:%d", &Hour, &Minute);
  config.wd_hour_start = Hour;
  config.wd_minute_start = Minute;
  sscanf(weekday_end.c_str(), "%d:%d", &Hour, &Minute);
  config.wd_hour_end = Hour;
  config.wd_minute_end = Minute;
  sscanf(weekend_start.c_str(), "%d:%d", &Hour, &Minute);
  config.we_hour_start = Hour;
  config.we_minute_start = Minute;
  sscanf(weekend_end.c_str(), "%d:%d", &Hour, &Minute);
  config.we_hour_end = Hour;
  config.we_minute_end = Minute;
  
  WriteConfig();

  request->send(200);
}


void api_nightmode_get(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__); 

  String result = "";
   result += "mode\n" + (String) config.nightmode + "\n\n";
   result += "weekday_start\n" + (String) config.wd_hour_start + ":" + config.wd_minute_start + "\n\n";
   result += "weekday_end\n" + (String) config.wd_hour_end + ":" + config.wd_minute_end + "\n\n";
   result += "weekend_start\n" + (String) config.we_hour_start + ":" + config.we_minute_start + "\n\n";
   result += "weekend_end\n" + (String) config.we_hour_end + ":" + config.we_minute_end + "\n\n";   
   result += "mode_type\nservos off\neverything off\n\n";

    Serial.println(result);
  
    request->send ( 200, "text/plain", result );

  
}



void api_nightmode(AsyncWebServerRequest *request)
{
    if(
      (request->hasParam("key") && checkLogin(request->getParam("key")->value())) ||
      (request->hasParam("key",true) && checkLogin(request->getParam("key", true)->value()))
    ){  	if(request->method() == HTTP_POST) {
  		api_nightmode_post(request);
  	}
  	else {
  		api_nightmode_get(request);
  	}
  }
  else {
    request->send (403,"text/plain", "Access Denied!");
  }
        
}


  
#endif
