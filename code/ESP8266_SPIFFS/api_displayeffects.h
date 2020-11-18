#ifndef API_DISPLAYEFFECTS_H
#define API_DISPLAYEFFECTS_H

void api_displayeffects_post(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__);
  
  config.brightness = request->getParam("brightness",true)->value().toInt();
  config.heffect = request->getParam("effect_hour",true)->value().toInt();
  config.meffect = request->getParam("effect_5minute",true)->value().toInt();
  config.dcolormode = request->getParam("color_mode_dot",true)->value().toInt();
  config.dcolor = request->getParam("color_dot",true)->value();
  config.wcolormode = request->getParam("color_mode_word",true)->value().toInt();
  config.wcolor = request->getParam("color_word",true)->value();
  config.bcolormode = request->getParam("color_mode_background",true)->value().toInt();
  config.bcolor = request->getParam("color_background",true)->value();    
  
  WriteConfig();

  // update display
  updateDisplay = true;

  request->send(200);
}


void api_displayeffects_get(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__); 

  String result = "";
   result += "brightness\n" + (String) config.brightness + "\n\n";
   result += "effect_hour\n" + (String) config.heffect + "\n\n";
   result += "effect_5minute\n" + (String) config.meffect + "\n\n";
   result += "color_mode_dot\n" + (String) config.dcolormode + "\n\n";
   result += "color_dot\n" + (String) config.dcolor + "\n\n";
   result += "color_mode_word\n" + (String) config.wcolormode + "\n\n";
   result += "color_word\n" + (String) config.wcolor + "\n\n";
   result += "color_mode_background\n" + (String) config.bcolormode + "\n\n";
   result += "color_background\n" + (String) config.bcolor + "\n\n";
   result += "effect_type\ntyping\nfade in\nfade out\ncolor mix\nrandom effect\n\n";
   result += "color_mode_dot_type\nfixed\nrandom\n\n";
   result += "color_mode_word_type\nfixed\nrandom\n\n";
   result += "color_mode_background_type\nfixed\nrandom\ncycle\n\n";
  
   request->send ( 200, "text/plain", result );

  
}



void api_displayeffects(AsyncWebServerRequest *request)
{
  if((request->hasParam("login") && request->getParam("login")->value() == config.login) || (request->hasParam("login",true) && request->getParam("login",true)->value() == config.login)){
  	if(request->method() == HTTP_POST) {
  		api_displayeffects_post(request);
  	}
  	else {
  		api_displayeffects_get(request);
  	}
  }
  else{
    request->send (403,"text/plain", "Access Denied!");
  }
        
}


  
#endif
