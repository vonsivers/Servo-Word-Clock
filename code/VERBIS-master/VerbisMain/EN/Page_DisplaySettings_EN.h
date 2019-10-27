#ifndef EN_PAGE_DISPLAYSETTINGS_EN_H
#define EN_PAGE_DISPLAYSETTINGS_EN_H

const char PAGE_ColorSettings[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Display Settings</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Start colour</td><td><input id="start-color" name="start-color" type="color" value="#000000" style="width:150px"></td></tr>
<tr><td align="right"></td><td> </td></tr>
<tr><td align="right">End colour</td><td><input id="end-color" name="end-color" type="color" value="#000000" style="width:150px"></td></tr>
<tr><td align="right"> </td><td></td></tr>
<tr><td align="right">'IT IS':</td><td><input type="checkbox" id="c_e_o" name="c_e_o"></td></tr>
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
        setValues("/admin/displayvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>
)=====";

void send_display_settings_html()
{
	Serial.println("************************************");
	Serial.println(server.args());

	  if (server.args() > 0 )  // Save Settings
	  {
	    String temp = "";
	    config.c_e_o = 0;
	    for ( uint8_t i = 0; i < server.args(); i++ ) {
	      if (server.argName(i) == "start-color") config.startColor = server.arg(i);
	      if (server.argName(i) == "end-color") config.endColor =  server.arg(i);
	      if (server.argName(i) == "c_e_o") config.c_e_o =  1;
	    }

	    Serial.println(config.startColor);
	    Serial.println(config.endColor);
	    WriteConfig();

	  }
	  server.send_P ( 200, "text/html", PAGE_ColorSettings );
	  Serial.println(__FUNCTION__);
}

void send_display_settings_values_html()
{

  String values ="";
  values += "start-color|" + (String) config.startColor + "|input\n";
  values += "end-color|" +  (String) config.endColor + "|input\n";
  values += "c_e_o|" +  (String) (config.c_e_o ? "checked" : "") + "|chk\n";
  Serial.println(values);
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;

}

#endif /* EN_PAGE_DISPLAYSETTINGS_EN_H */
