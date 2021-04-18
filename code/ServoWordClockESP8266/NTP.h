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

#ifndef NTP_H
#define NTP_H

/*
**
**  NTP
**
*/

// update the global time structure
void updateTimeStruct() {
  time(&now);                       // read the current time
  localtime_r(&now, &tm);           // update the structure tm with the current time
}

// for manual timesetting
void setTimeUser(int hh, int mm, int ss, int dd, int mon, int yy) { 
  Serial.println("time set by user");
  configTime(TZ_Etc_UTC , NULL); // set timezone to UTC (no NTP server)
  sntp_stop(); // stop NTP update
  struct tm usertime;
  usertime.tm_hour = hh;
  usertime.tm_min = mm;
  usertime.tm_sec = ss;
  usertime.tm_mday = dd;
  usertime.tm_mon = mon - 1; // months start from 0
  usertime.tm_year = yy - 1900; // year starts from 1900
  time_t epoch = mktime(&usertime);
  timeval tv = { epoch, 0 };
  settimeofday(&tv, NULL);
}

// triggered by callback function when time is set by user or NTP
void time_is_set() {
  // in CONT stack, unlike ISRs,
  // any function is allowed in this callback
  Serial.println("time was set!");
  time_was_set = true;
  updateDisplay = true;   // always update display after time change
  updateTimeStruct();
}


// configure NTP server and timezone
void initNTP() {
  Serial.println("configure NTP server");
  switch (config.timeZone) {
    case 0:
      configTime(TZ_Europe_Berlin, "pool.ntp.org");
      break;
    case 1:
      configTime(TZ_America_New_York, "pool.ntp.org");
      break;
    case 2:
      configTime(TZ_America_Los_Angeles, "pool.ntp.org");
      break;
    case 3:
      configTime(TZ_Europe_London, "pool.ntp.org");
      break;
    default:
      configTime(TZ_Europe_Berlin, "pool.ntp.org");
  }

}

// gets called every second by main loop
void ISRsecondTick()
{
  // update time structure if time was set by user or NTP
  if(time_was_set) {
    updateTimeStruct();
  }
  
}



#endif
