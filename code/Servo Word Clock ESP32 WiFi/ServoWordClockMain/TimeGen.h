#ifndef TIMEGEN_H
#define TIMEGEN_H

void Gen_Time() {
	  if ((ntp_response_ok == true or manual_time_set == true) and date_ok == true) {

    // check if night mode is active
    //
    long current_minute = DateTime.hour*60 + DateTime.minute;
    // weekdays (Sunday = 1)
    if(DateTime.wday>1 && DateTime.wday<7) {
      long minute_start = config.wd_hour_start*60 + config.wd_minute_start;
      long minute_end = config.wd_hour_end*60 + config.wd_minute_end;
      // change to night mode
      if( (current_minute>=minute_start && current_minute<minute_end && minute_start<minute_end) || ( (current_minute>=minute_start || current_minute<minute_end) && minute_start>minute_end) ) {
        if(currentMode!=config.nightmode) {
          config.clockmode = config.nightmode;
          updateDisplay = true;
        }
      }
      // change to normal mode
      else {
        if(currentMode!="normal") {
          config.clockmode = "normal";
          updateDisplay = true;
        }
      }
    }
    // weekends
    else {
      long minute_start = config.we_hour_start*60 + config.we_minute_start;
      long minute_end = config.we_hour_end*60 + config.we_minute_end;
      // change to night mode
      if( (current_minute>=minute_start && current_minute<minute_end && minute_start<minute_end) || ( (current_minute>=minute_start || current_minute<minute_end) && minute_start>minute_end) ) {
        if(currentMode!=config.nightmode) {
          config.clockmode = config.nightmode;
          updateDisplay = true;
        }
      }
      // change to normal mode
      else {
        if(currentMode!="normal") {
          config.clockmode = "normal";
          updateDisplay = true;
        }
      }
    }

      // update display every 5 minutes or if requested
      if(updateDisplay || ((DateTime.minute % 5) == 0 && DateTime.minute > lastmin) || (DateTime.minute == 0 && lastmin == 59)) {
        Serial.printf("Current Time: %d:%d:%d\n", DateTime.hour,DateTime.minute,DateTime.second);
        updateTime();
        lastmin = DateTime.minute;
        updateDisplay = false;
      }
      
      // update dots every minute
      else if((DateTime.minute > lastmin) || (DateTime.minute == 0 && lastmin == 59)) {
        Serial.printf("Current Time: %d:%d:%d\n", DateTime.hour,DateTime.minute,DateTime.second);
        updateMinutes("effect1");
        lastmin = DateTime.minute;  
      }

      // color cycle LEDs
      if(config.bcolormode=="cycle") {
        EVERY_N_MILLISECONDS( 50 ) {updateBkgColor(); }
      }
      
  }
}


#endif /* EN_TIMEGEN_EN_H */
