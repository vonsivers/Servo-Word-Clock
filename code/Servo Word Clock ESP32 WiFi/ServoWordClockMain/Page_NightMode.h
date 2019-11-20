#ifndef PAGE_NIGHTMODE_H
#define PAGE_NIGHTMODE_H

const char PAGE_NightMode[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Night mode settings</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td>Night mode</td><td>
<select  id="nmode" name="nightmode">
  <option value="off">off</option>
  <option value="silent">silent</option>
</select>
</td></tr>
<tr><td><strong>Weekdays</strong></td></tr>
<tr><td>Start time</td><td align="right">H:</td><td><input type="text" id="wd_hour_start" name="wd_hour_start" size="3" maxlength="2" value=""></td><td align="right">M:</td><td><input type="text" id="wd_minute_start" name="wd_minute_start" size="3" maxlength="2" value=""></td></tr>
<tr><td>End time</td><td align="right">H:</td><td><input type="text" id="wd_hour_end" name="wd_hour_end" size="3" maxlength="2" value=""></td><td align="right">M:</td><td><input type="text" id="wd_minute_end" name="wd_minute_end" size="3" maxlength="2" value=""></td></tr>
<tr><td><strong>Weekends</strong></td></tr>
<tr><td>Start time</td><td align="right">H:</td><td><input type="text" id="we_hour_start" name="we_hour_start" size="3" maxlength="2" value=""></td><td align="right">M:</td><td><input type="text" id="we_minute_start" name="we_minute_start" size="3" maxlength="2" value=""></td></tr>
<tr><td>End time</td><td align="right">H:</td><td><input type="text" id="we_hour_end" name="we_hour_end" size="3" maxlength="2" value=""></td><td align="right">M:</td><td><input type="text" id="we_minute_end" name="we_minute_end" size="3" maxlength="2" value=""></td></tr>
<tr><td colspan="5" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
</form>
<script>

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/nightmode");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";

void send_night_mode_html(AsyncWebServerRequest *request)
{
  if (request->args() > 0 )  // Save Settings
  {
    for ( uint8_t i = 0; i < request->args(); i++ ) {
      if (request->argName(i) == "nmode") config.nightmode = request->arg(i);
      if (request->argName(i) == "wd_hour_start") config.wd_hour_start = request->arg(i).toInt();
      if (request->argName(i) == "wd_minute_start") config.wd_minute_start = request->arg(i).toInt();
      if (request->argName(i) == "wd_hour_end") config.wd_hour_end = request->arg(i).toInt();
      if (request->argName(i) == "wd_minute_end") config.wd_minute_end = request->arg(i).toInt();
      if (request->argName(i) == "we_hour_start") config.we_hour_start = request->arg(i).toInt();
      if (request->argName(i) == "we_minute_start") config.we_minute_start = request->arg(i).toInt();
      if (request->argName(i) == "we_hour_end") config.we_hour_end = request->arg(i).toInt();
      if (request->argName(i) == "we_minute_end") config.we_minute_end = request->arg(i).toInt();
    }
    // update display
    updateDisplay = true;
  }
  request->send_P ( 200, "text/html", PAGE_NightMode );
  Serial.println(__FUNCTION__);

}

void send_night_mode_values_html(AsyncWebServerRequest *request)
{

  String values ="";
  values += "nmode|" + (String) config.nightmode + "|input\n";
  values += "wd_hour_start|" +  (String) config.wd_hour_start + "|input\n";
  values += "wd_minute_start|" +  (String) config.wd_minute_start + "|input\n";
  values += "wd_hour_end|" +  (String) config.wd_hour_end + "|input\n";
  values += "wd_minute_end|" +  (String) config.wd_minute_end + "|input\n";
  values += "we_hour_start|" +  (String) config.we_hour_start + "|input\n";
  values += "we_minute_start|" +  (String) config.we_minute_start + "|input\n";
  values += "we_hour_end|" +  (String) config.we_hour_end + "|input\n";
  values += "we_minute_end|" +  (String) config.we_minute_end + "|input\n";
  request->send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;
}

#endif /* EN_PAGE_NIGHTMODE_EN_H */
