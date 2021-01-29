#ifndef API_CHANGEPWD_H
#define API_CHANGEPWD_H


void api_changepwd_post(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__);

  if(request->hasParam("newlogin",true) && !request->getParam("newlogin",true)->value().isEmpty()){
	  config.login = request->getParam("newlogin",true)->value();
	  WriteConfig();
  }
  request->send(200);
}

void api_changepwd(AsyncWebServerRequest *request)
{   
  if(
      (request->hasParam("key") && checkLogin(request->getParam("key")->value())) ||
      (request->hasParam("key",true) && checkLogin(request->getParam("key", true)->value()))
    ){    if(request->method() == HTTP_POST) {
      api_changepwd_post(request);
    }
    else {
      request->send (403,"text/plain", "Access Denied!");
    }
  }
  else {
    request->send (403,"text/plain", "Access Denied!");
  }
}
  
#endif
