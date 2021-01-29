#ifndef API_LOGIN_H
#define API_LOGIN_H


void api_login_post(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__);

  loginkey = createRandString();
  logintimestamp = millis();
  request->send(200, "text/plain", loginkey);
}

void api_login(AsyncWebServerRequest *request)
{   
  if(request->method() == HTTP_POST) {
	  if(request->getParam("login",true)->value() == config.login){
			api_login_post(request);
		}
    else {
      request->send (403,"text/plain", "Access Denied!");
    }
	}
	else{
    if(
      (request->hasParam("key") && checkLogin(request->getParam("key")->value())) ||
      (request->hasParam("key",true) && checkLogin(request->getParam("key", true)->value()))
    ){
      request->send(200, "text/plain", loginkey);
    }else{
      request->send (403,"text/plain", "Access Denied!");
    }
	}
}
  
#endif
