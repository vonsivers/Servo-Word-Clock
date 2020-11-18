#ifndef API_LOGIN_H
#define API_LOGIN_H


void api_login_post(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__);
  
  if(!request->getParam("newlogin",true)->value().isEmpty()){
	  config.login = request->getParam("newlogin",true)->value();
	  WriteConfig();
  }

  request->send(200);
}

void api_login(AsyncWebServerRequest *request)
{
	if(request->getParam("login",true)->value() == config.login){
		if(request->method() == HTTP_POST) {
			api_login_post(request);
		}
	}
	else{
		request->send (403,"text/plain", "Access Denied!");
	}
}
  
#endif
