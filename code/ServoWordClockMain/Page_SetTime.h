/*
    This file is part of Servo Wordclock.

    Servo Wordclock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Servo Wordclock is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Servo Wordclock.  If not, see <https://www.gnu.org/licenses/>.
 
    based on VERBIS by Andrei Erdei - https://github.com/ancalex/VERBIS
    modifed by Moritz v. Sivers, 25.11.2019
    
    Copyright 2019 Moritz v. Sivers
 */

#ifndef PAGE_SETTIME_H
#define PAGE_SETTIME_H

const char PAGE_SetTime[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Manual time setting</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Hour:</td><td><input type="text" id="set_hour" name="set_hour" size="3" maxlength="2" value=""></td></tr>
<tr><td align="right">Minute:</td><td><input type="text" id="set_minute" name="set_minute" size="3" maxlength="2" value=""></td></tr>
<tr><td align="right">Second:</td><td><input type="text" id="set_second" name="set_second" size="3" maxlength="2" value=""></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
</form>
<script>

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/timevalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";

void send_Time_Set_html(AsyncWebServerRequest *request)
{
  if(!request->authenticate(http_username, http_password))
        return request->requestAuthentication();
        
  if (request->args() > 0 )  // Save Settings
  {
    for ( uint8_t i = 0; i < request->args(); i++ ) {
      if (request->argName(i) == "set_hour") DateTime.hour = request->arg(i).toInt();
      if (request->argName(i) == "set_minute") DateTime.minute = request->arg(i).toInt();
      if (request->argName(i) == "set_second") DateTime.second = request->arg(i).toInt();
    }
    manual_time_set = true;
    UnixTimestamp = (DateTime.hour*3600 + DateTime.minute*60 + DateTime.second - config.timeZone*360);
    ISRsecondTick();
    // update display
    updateDisplay = true;
  }
  request->send_P ( 200, "text/html", PAGE_SetTime );
  Serial.println(__FUNCTION__);

}

void send_Time_Set_values_html(AsyncWebServerRequest *request)
{

  String values ="";
  values += "set_hour|" + (String) DateTime.hour + "|input\n";
  values += "set_minute|" +  (String) DateTime.minute + "|input\n";
  values += "set_second|" +  (String) DateTime.second + "|input\n";
  request->send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;
}

#endif /* EN_PAGE_SETTIME_EN_H */
