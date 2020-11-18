#ifndef API_WIFI_H
#define API_WIFI_H


void api_wifi_post(AsyncWebServerRequest *request) {
  
  Serial.println(__FUNCTION__);
  
  config.ssid = request->getParam("ssid",true)->value();
  config.password = request->getParam("password",true)->value();
  
  WriteConfig();

  request->send(200);

  Serial.println("---------- restarting ESP -----------");
  ESP.restart();
}


void api_wifi_get(AsyncWebServerRequest *request) {
  
	Serial.println(__FUNCTION__); 

  String state = "N/A";
  if (WiFi.status() == 0) state = "Idle";
  else if (WiFi.status() == 1) state = "NO SSID AVAILABLE";
  else if (WiFi.status() == 2) state = "SCAN COMPLETED";
  else if (WiFi.status() == 3) state = "CONNECTED";
  else if (WiFi.status() == 4) state = "CONNECT FAILED";
  else if (WiFi.status() == 5) state = "CONNECTION LOST";
  else if (WiFi.status() == 6) state = "DISCONNECTED";
  
	String result = "";
	result += "ssid\n" + (String) config.ssid + "\n\n";
	result += "password\n" + (String) config.password + "\n\n";
  result += "state\n" + state;
     
  request->send ( 200, "text/plain", result );
  
}



void api_wifi(AsyncWebServerRequest *request)
{
	if((request->hasParam("login") && request->getParam("login")->value() == config.login) || (request->hasParam("login",true) && request->getParam("login",true)->value() == config.login)){
		if(request->method() == HTTP_POST) {
			api_wifi_post(request);
		}
		else {
			api_wifi_get(request);
		}
	}
	else{
		request->send (403,"text/plain", "Access Denied!");
	}
}
#endif
