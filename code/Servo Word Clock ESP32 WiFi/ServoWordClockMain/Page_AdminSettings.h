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
 
#ifndef PAGE_ADMINSETTINGS_H
#define PAGE_ADMINSETTINGS_H

const char PAGE_AdminSettings[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Admin Settings</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Factory Reset:</td><td><input type="checkbox" id="reset" name="reset"></td></tr>
<tr><td align="right">DHCP:</td><td><input type="checkbox" id="dhcp" name="dhcp"></td></tr>
<tr><td align="right">SSID:</td><td><input type="text" id="ssid" name="ssid" value=""></td></tr>
<tr><td align="right">Password:</td><td><input type="text" id="password" name="password" value=""></td></tr>
<tr><td align="right">IP:     </td><td><input type="text" id="ip_0" name="ip_0" size="3">.<input type="text" id="ip_1" name="ip_1" size="3">.<input type="text" id="ip_2" name="ip_2" size="3">.<input type="text" id="ip_3" name="ip_3" value="" size="3"></td></tr>
<tr><td align="right">Netmask:</td><td><input type="text" id="nm_0" name="nm_0" size="3">.<input type="text" id="nm_1" name="nm_1" size="3">.<input type="text" id="nm_2" name="nm_2" size="3">.<input type="text" id="nm_3" name="nm_3" size="3"></td></tr>
<tr><td align="right">Gateway:</td><td><input type="text" id="gw_0" name="gw_0" size="3">.<input type="text" id="gw_1" name="gw_1" size="3">.<input type="text" id="gw_2" name="gw_2" size="3">.<input type="text" id="gw_3" name="gw_3" size="3"></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:180px" class="btn btn--m btn--blue" value="Save & Restart"></td></tr>
</table>
</form>
<hr>
<strong>Connection State:</strong><div id="connectionstate">N/A</div>
<hr>
<strong>Networks:</strong><br>
<table border="0"  cellspacing="3" style="width:310px" >
<tr><td><div id="networks">Scanning...</div></td></tr>
<tr><td align="center"><a href="javascript:GetState()" style="width:150px" class="btn btn--m btn--blue">Refresh</a></td></tr>
</table>


<script>

function GetState()
{
  setValues("/admin/connectionstate");
}
function selssid(value)
{
  document.getElementById("ssid").value = value; 
}

  
window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/adminvalues");
        setTimeout(GetState,3000);
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>
)=====";


const char PAGE_WaitAndReloadAdvanced[] PROGMEM = R"=====(
<meta http-equiv="refresh" content="5; URL=advanced.html">
Please Wait....Configuring and Restarting.
)=====";

void send_admin_settings_html(AsyncWebServerRequest *request)
{
  if(!request->authenticate(http_username, http_password))
        return request->requestAuthentication();
        
	if (request->args() > 0 )  // Save Settings
  {
    String temp = "";
    config.dhcp = false;
    bool isReset = false;
    for ( uint8_t i = 0; i < request->args(); i++ ) {
      if (request->argName(i) == "ip_0") if (checkRange(request->arg(i)))   config.IP[0] =  request->arg(i).toInt();
      if (request->argName(i) == "ip_1") if (checkRange(request->arg(i)))   config.IP[1] =  request->arg(i).toInt();
      if (request->argName(i) == "ip_2") if (checkRange(request->arg(i)))   config.IP[2] =  request->arg(i).toInt();
      if (request->argName(i) == "ip_3") if (checkRange(request->arg(i)))   config.IP[3] =  request->arg(i).toInt();
      if (request->argName(i) == "nm_0") if (checkRange(request->arg(i)))   config.Netmask[0] =  request->arg(i).toInt();
      if (request->argName(i) == "nm_1") if (checkRange(request->arg(i)))   config.Netmask[1] =  request->arg(i).toInt();
      if (request->argName(i) == "nm_2") if (checkRange(request->arg(i)))   config.Netmask[2] =  request->arg(i).toInt();
      if (request->argName(i) == "nm_3") if (checkRange(request->arg(i)))   config.Netmask[3] =  request->arg(i).toInt();
      if (request->argName(i) == "gw_0") if (checkRange(request->arg(i)))   config.Gateway[0] =  request->arg(i).toInt();
      if (request->argName(i) == "gw_1") if (checkRange(request->arg(i)))   config.Gateway[1] =  request->arg(i).toInt();
      if (request->argName(i) == "gw_2") if (checkRange(request->arg(i)))   config.Gateway[2] =  request->arg(i).toInt();
      if (request->argName(i) == "gw_3") if (checkRange(request->arg(i)))   config.Gateway[3] =  request->arg(i).toInt();
      if (request->argName(i) == "dhcp") config.dhcp = true;
      if (request->argName(i) == "reset") isReset = true;
    }
    
    request->send_P ( 200, "text/html", PAGE_WaitAndReloadAdvanced );
    
    WriteConfig();
    // factory reset
    if(isReset) {
      Serial.println("Reset to Factory Settings!");
      ClearConfig(); 
    }
    AdminTimeOutCounter=0;
    delay(3000);
    ESP.restart();

  }
  else
  {
    request->send_P ( 200, "text/html", PAGE_AdminSettings );
  }
  Serial.println(__FUNCTION__);
}

void send_admin_settings_values_html(AsyncWebServerRequest *request)
{

  String values ="";
  values += "ssid|" + (String) config.ssid + "|input\n";
  values += "password|" +  (String) config.password + "|input\n";
  values += "ip_0|" +  (String) config.IP[0] + "|input\n";
	values += "ip_1|" +  (String) config.IP[1] + "|input\n";
	values += "ip_2|" +  (String) config.IP[2] + "|input\n";
	values += "ip_3|" +  (String) config.IP[3] + "|input\n";
	values += "nm_0|" +  (String) config.Netmask[0] + "|input\n";
	values += "nm_1|" +  (String) config.Netmask[1] + "|input\n";
	values += "nm_2|" +  (String) config.Netmask[2] + "|input\n";
	values += "nm_3|" +  (String) config.Netmask[3] + "|input\n";
	values += "gw_0|" +  (String) config.Gateway[0] + "|input\n";
	values += "gw_1|" +  (String) config.Gateway[1] + "|input\n";
	values += "gw_2|" +  (String) config.Gateway[2] + "|input\n";
	values += "gw_3|" +  (String) config.Gateway[3] + "|input\n";
	values += "dhcp|" +  (String) (config.dhcp ? "checked" : "") + "|chk\n";

  Serial.println(values);
  request->send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;

}



#endif /* EN_PAGE_DISPLAYSETTINGS_EN_H */
