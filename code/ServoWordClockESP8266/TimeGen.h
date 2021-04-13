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
    
    Copyright 2021, Moritz v. Sivers
 */

#ifndef TIMEGEN_H
#define TIMEGEN_H

void Gen_Time() {
  // check if night mode is active
  //
  long current_minute = tm.tm_hour*60 + tm.tm_min;
  // weekdays (Sunday=0)
  if(tm.tm_wday>0 && tm.tm_wday<6) {
    long minute_start = config.wd_hour_start*60 + config.wd_minute_start;
    long minute_end = config.wd_hour_end*60 + config.wd_minute_end;
    // change to night mode
    if( (current_minute>=minute_start && current_minute<minute_end && minute_start<minute_end) || ( (current_minute>=minute_start || current_minute<minute_end) && minute_start>minute_end) ) {
      if(currentMode!=config.nightmode) {
        config.clockmode = config.nightmode;
        updateDisplay = true;
        WriteConfig();    // save current clock mode
      }
    }
    // change to normal mode
    else {
      if(currentMode!="normal") {
        config.clockmode = "normal";
        updateDisplay = true;
        WriteConfig();    // save current clock mode
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
        WriteConfig();    // save current clock mode
        updateDisplay = true;
      }
    }
    // change to normal mode
    else {
      if(currentMode!="normal") {
        config.clockmode = "normal";
        updateDisplay = true;
        WriteConfig();    // save current clock mode
      }
    }
  }

  // update display every 5 minutes or if requested
  if(updateDisplay || ((tm.tm_min % 5) == 0 && tm.tm_min > lastmin) || (tm.tm_min == 0 && lastmin == 59)) {
    Serial.printf("Current Time: %d:%d:%d\n", tm.tm_hour,tm.tm_min,tm.tm_sec);
    updateTime();
    lastmin = tm.tm_min;
    updateDisplay = false;
  }
  
  // update dots every minute
  else if((tm.tm_min > lastmin) || (tm.tm_min == 0 && lastmin == 59)) {
    Serial.printf("Current Time: %d:%d:%d\n", tm.tm_hour,tm.tm_min,tm.tm_sec);
    updateMinutes("effect1");
    lastmin = tm.tm_min;  
  }

  // color cycle LEDs
  if(config.bcolormode=="cycle") {
    EVERY_N_MILLISECONDS( 50 ) {updateBkgColor(); }
  }
      
  
}


#endif /* EN_TIMEGEN_EN_H */
