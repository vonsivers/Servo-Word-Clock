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

void time_is_set(bool from_sntp /* <= this parameter is optional */) {
  // in CONT stack, unlike ISRs,
  // any function is allowed in this callback

  Serial.print("settimeofday(");
  if (from_sntp) {
    Serial.print("SNTP");
  } else {
    Serial.print("USER");
  }
  Serial.print(")");

  time_was_set = true;
}

void initNTP() {
  String timeZone;
  switch (config.timeZone) {
    case 10:
      timeZone = "CET-1CEST,M3.5.0,M10.5.0/3";
      break;
    default:
      timeZone = "GMT0";
  }
  configTime(timeZone,ntpServerName);
}


void ISRsecondTick()
{
  // if time was set by user or NTP
  if(time_was_set) {
    time(&now);                       // read the current time
    localtime_r(&now, &tm);           // update the structure tm with the current time
  }
  
}



#endif
