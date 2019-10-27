#ifndef PAGE_DISPLAYSETTINGS_H
#define PAGE_DISPLAYSETTINGS_H

const char PAGE_ColorSettings[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Display Settings</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td>Clock mode</td><td>
<select  id="cmode" name="cmode">
  <option value="normal">normal</option>
  <option value="silent">silent</option>
</select>
</td></tr>
<tr><td>Brightness</td><td><input type="range" min="1" max="255" value="200" id="brightness" name="brightness"></td></tr>
<tr><td>Hour effect</td><td>
<select id="heffect" name="heffect">
  <option value="effect1">typing</option>
  <option value="effect2">fade in</option>
  <option value="effect3">fade out</option>
  <option value="effect4">color mix</option>
  <option value="random">random effect</option>
</select>
</td></tr>
<tr><td>5 minute effect</td><td>
<select id="meffect" name="meffect">
  <option value="effect1">typing</option>
  <option value="effect2">fade in</option>
  <option value="effect3">fade out</option>
  <option value="effect4">color mix</option>
  <option value="random">random effect</option>
</select>
</td></tr>
<tr><td>Dot color mode</td><td>
<select id="dcolormode" name="dcolormode">
  <option value="random">random</option>
  <option value="fixed">fixed</option>
</select>
</td></tr>
<tr><td align="right">Dot color</td><td><input type="color" name="dcolor" id="dcolor" value="#ff0000" style="width:150px"></td></tr>
<tr><td>Word color mode</td><td>
<select id="wcolormode" name="wcolormode">
  <option value="random">random</option>
  <option value="fixed">fixed</option>
</select>
</td></tr>
<tr><td align="right">Word color</td><td><input type="color" name="wcolor" id="wcolor" value="#ff0000" style="width:150px"></td></tr>
<tr><td>Background color mode</td><td>
<select id="bcolormode" name="bcolormode">
  <option value="random">random</option>
  <option value="cycle">cycle</option>
  <option value="fixed">fixed</option>
</select>
</td></tr>
<tr><td align="right">Background color</td><td><input type="color" name="bcolor" id="bcolor" value="#0000cc" style="width:150px"></td></tr>
<tr><td align="right"> </td><td></td></tr>
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

void send_display_settings_html(AsyncWebServerRequest *request)
{
	Serial.println("************************************");
	Serial.println(request->args());

	  if (request->args() > 0 )  // Save Settings
	  {
	    //for ( uint8_t i = 0; i < request->args(); i++ ) {
      for ( uint8_t i = 0; i <request->args(); i++ ) {
	      if (request->argName(i) == "cmode") config.clockmode = request->arg(i);
	      if (request->argName(i) == "brightness") config.brightness =  request->arg(i).toInt();
	      if (request->argName(i) == "heffect") config.heffect =  request->arg(i);
        if (request->argName(i) == "meffect") config.meffect =  request->arg(i);
        if (request->argName(i) == "dcolormode") config.dcolormode =  request->arg(i);
        if (request->argName(i) == "dcolor") config.dcolor =  request->arg(i);
        if (request->argName(i) == "wcolormode") config.wcolormode =  request->arg(i);
        if (request->argName(i) == "wcolor") config.wcolor =  request->arg(i);
        if (request->argName(i) == "bcolormode") config.bcolormode =  request->arg(i);
        if (request->argName(i) == "bcolor") config.bcolor =  request->arg(i);
	    }

	    Serial.println(config.clockmode);
      Serial.println(config.brightness);
      Serial.println(config.heffect);
      Serial.println(config.meffect);
      Serial.println(config.dcolormode);
      Serial.println(config.dcolor);
      Serial.println(config.wcolormode);
      Serial.println(config.wcolor);
      Serial.println(config.bcolormode);
      Serial.println(config.bcolor);
	    WriteConfig();

      // update display
      updateDisplay = true;

	  }
	  request->send_P ( 200, "text/html", PAGE_ColorSettings );
	  Serial.println(__FUNCTION__);
}

void send_display_settings_values_html(AsyncWebServerRequest *request)
{

  String values ="";
  values += "cmode|" + (String) config.clockmode + "|input\n";
  values += "brightness|" +  (String) config.brightness + "|input\n"; //
  values += "heffect|" +  (String) config.heffect + "|input\n";
  values += "meffect|" +  (String) config.meffect + "|input\n";
  values += "dcolormode|" +  (String) config.dcolormode + "|input\n";
  values += "dcolor|" +  (String) config.dcolor + "|input\n";
  values += "wcolormode|" +  (String) config.wcolormode + "|input\n";
  values += "wcolor|" +  (String) config.wcolor + "|input\n";
  values += "bcolormode|" +  (String) config.bcolormode + "|input\n";
  values += "bcolor|" +  (String) config.bcolor + "|input\n";

  Serial.println(values);
  request->send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;

}

#endif /* EN_PAGE_DISPLAYSETTINGS_EN_H */
