#ifndef TIMEGEN_H
#define TIMEGEN_H

void Gen_Time() {
	  if ((ntp_response_ok == true or manual_time_set == true) and date_ok == true) {

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
