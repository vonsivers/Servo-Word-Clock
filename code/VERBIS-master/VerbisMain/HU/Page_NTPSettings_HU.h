#ifndef HU_PAGE_NTPSETTINGS_HU_H
#define HU_PAGE_NTPSETTINGS_HU_H

const char PAGE_NTPConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Id&#337; server be&#225;ll&#237;t&#225;sok</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Id&#337; server:</td><td><input type="text" id="ntpserver" name="ntpserver" maxlength="172" value=""></td></tr>
<tr><td align="right">&#211;ra frissit&#233;s:</td><td><input type="text" id="update" name="update" size="3"maxlength="6" value=""> percenk&#233;nt (0=le&#225;ll&#237;tva)</td></tr>
<tr><td>Id&#337; z&#243;na</td><td>
<select  id="tz" name="tz">
  <option value="-120">(GMT-12:00)</option>
  <option value="-110">(GMT-11:00)</option>
  <option value="-100">(GMT-10:00)</option>
  <option value="-90">(GMT-09:00)</option>
  <option value="-80">(GMT-08:00)</option>
  <option value="-70">(GMT-07:00)</option>
  <option value="-60">(GMT-06:00)</option>
  <option value="-50">(GMT-05:00)</option>
  <option value="-40">(GMT-04:00)</option>
  <option value="-35">(GMT-03:30)</option>
  <option value="-30">(GMT-03:00)</option>
  <option value="-20">(GMT-02:00)</option>
  <option value="-10">(GMT-01:00)</option>
  <option value="0">(GMT+00:00)</option>
  <option value="10">(GMT+01:00)</option>
  <option value="20">(GMT+02:00)</option>
  <option value="30">(GMT+03:00)</option>
  <option value="35">(GMT+03:30)</option>
  <option value="40">(GMT+04:00)</option>
  <option value="45">(GMT+04:30)</option>
  <option value="50">(GMT+05:00)</option>
  <option value="55">(GMT+05:30)</option>
  <option value="57">(GMT+05:45)</option>
  <option value="60">(GMT+06:00)</option>
  <option value="65">(GMT+06:30)</option>
  <option value="70">(GMT+07:00)</option>
  <option value="80">(GMT+08:00)</option>
  <option value="90">(GMT+09:00)</option>
  <option value="95">(GMT+09:30)</option>
  <option value="100">(GMT+10:00)</option>
  <option value="110">(GMT+11:00)</option>
  <option value="120">(GMT+12:00)</option>
  <option value="120">(GMT+12:00)</option>
  <option value="130">(GMT+13:00)</option>
</select>
</td></tr>
<tr><td align="right">Ny&#225;ri id&#337;sz&#225;m&#237;t&#225;s:</td><td><input type="checkbox" id="dst" name="dst"></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Ment&#233;s"></td></tr>
</table>
</form>
<script>
  

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/ntpvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}


</script>
)=====";


void send_NTP_configuration_html()
{
  if (server.args() > 0 )  // Save Settings
  {
    config.isDayLightSaving = false;
    String temp = "";
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "ntpserver") config.ntpServerName = urldecode( server.arg(i));
      if (server.argName(i) == "update") config.Update_Time_Via_NTP_Every =  server.arg(i).toInt();
      if (server.argName(i) == "tz") config.timeZone =  server.arg(i).toInt();
      if (server.argName(i) == "dst") config.isDayLightSaving = true;
    }
    WriteConfig();

    firstStart = true;
  }
  server.send_P ( 200, "text/html", PAGE_NTPConfiguration );
  Serial.println(__FUNCTION__);

}

void send_NTP_configuration_values_html()
{

  String values ="";
  values += "ntpserver|" + (String) config.ntpServerName + "|input\n";
  values += "update|" +  (String) config.Update_Time_Via_NTP_Every + "|input\n";
  values += "tz|" +  (String) config.timeZone + "|input\n";
  values += "dst|" +  (String) (config.isDayLightSaving ? "checked" : "") + "|chk\n";
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;
}

#endif /* HU_PAGE_NTPSETTINGS_HU_H */
