#ifndef EN_TIMEGEN_EN_H
#define EN_TIMEGEN_EN_H

void Gen_Hour() {
if ( config.isFormat24h == 0 && DateTime.hour > 12) {
	temp_Hour = temp_Hour - 12;
}
	switch (temp_Hour) {
	case 0: {
		HOUR = HOUR + C_zero;
	}
		break;
	case 1: {
		HOUR = HOUR + C_one;
	}
		break;
	case 2: {
		HOUR = HOUR + C_two;
	}
		break;
	case 3: {
		HOUR = HOUR + C_three;
	}
		break;
	case 4: {
		HOUR = HOUR + C_four;
	}
		break;
	case 5: {
		HOUR = HOUR + C_five;
	}
		break;
	case 6: {
		HOUR = HOUR + C_six;
	}
		break;
	case 7: {
		HOUR = HOUR + C_seven;
	}
		break;
	case 8: {
		HOUR = HOUR + C_eight;
	}
		break;
	case 9: {
		HOUR = HOUR + C_nine;
	}
		break;
	case 10: {
		HOUR = HOUR + C_ten;
	}
		break;
	case 11: {
		HOUR = HOUR + C_eleven;
	}
		break;
	case 12:
	case 24:
	{
		HOUR = HOUR + C_twelve;
	}
		break;
	case 13: {
		HOUR = HOUR + C_thirteen;
	}
		break;
	case 14: {
		HOUR = HOUR + C_fourteen;
	}
		break;
	case 15: {
		HOUR = HOUR + C_fifteen;
	}
		break;
	case 16: {
		HOUR = HOUR + C_sixteen;
	}
		break;
	case 17: {
		HOUR = HOUR + C_seventeen;
	}
		break;
	case 18: {
		HOUR = HOUR + C_eighteen;
	}
		break;
	case 19: {
		HOUR = HOUR + C_nineteen;
	}
		break;
	case 20: {
		HOUR = HOUR + C_twenty;
	}
		break;
	case 21: {
		HOUR = HOUR + C_twentyone;
	}
		break;
	case 22: {
		HOUR = HOUR + C_twentytwo;
	}
		break;
	case 23: {
		HOUR = HOUR + C_twentythree;
	}
		break;
 }
}

//==================

void Gen_Minute () {
 switch (DateTime.minute) {
  case 0:
  {
   //HOUR = HOUR + C_oclock;
  }
  break;
  case 1:
  case 59:
  {
   HOUR = HOUR + C_one;
  }
  break;
  case 2:
  case 58:
  {
   HOUR = HOUR + C_two;
  }
  break;
    case 3:
    case 57:
  {
   HOUR = HOUR + C_three;
  }
  break;
    case 4:
    case 56:
  {
   HOUR = HOUR + C_four;
  }
  break;
    case 5:
    case 55:
  {
   HOUR = HOUR + C_five;
  }
  break;
    case 6:
    case 54:
  {
   HOUR = HOUR + C_six;
  }
  break;
    case 7:
    case 53:
  {
   HOUR = HOUR + C_seven;
  }
  break;
    case 8:
    case 52:
  {
   HOUR = HOUR + C_eight;
  }
  break;
    case 9:
    case 51:
  {
   HOUR = HOUR + C_nine;
  }
  break;
    case 10:
    case 50:
  {
   HOUR = HOUR + C_ten;
  }
  break;
    case 11:
    case 49:
  {
   HOUR = HOUR + C_eleven;
  }
  break;
    case 12:
    case 48:
  {
   HOUR = HOUR + C_twelve;
  }
  break;
    case 13:
    case 47:
  {
   HOUR = HOUR + C_thirteen;
  }
  break;
    case 14:
    case 46:
  {
   HOUR = HOUR + C_fourteen;
  }
  break;
    case 15:
    case 45:
  {
   HOUR = HOUR + C_fifteen;
  }
  break;
    case 16:
    case 44:
  {
   HOUR = HOUR + C_sixteen;
  }
  break;
    case 17:
    case 43:
  {
   HOUR = HOUR + C_seventeen;
  }
  break;
    case 18:
    case 42:
  {
   HOUR = HOUR + C_eighteen;
  }
  break;
    case 19:
    case 41:
  {
   HOUR = HOUR + C_nineteen;
  }
  break;
    case 20:
    case 40:
  {
   HOUR = HOUR + C_twenty;
  }
  break;
    case 21:
    case 39:
  {
   HOUR = HOUR + C_twentyone;
  }
  break;
    case 22:
    case 38:
  {
   HOUR = HOUR + C_twentytwo;
  }
  break;
    case 23:
    case 37:
  {
   HOUR = HOUR + C_twentythree;
  }
  break;
    case 24:
    case 36:
  {
   HOUR = HOUR + C_twentyfour;
  }
  break;
    case 25:
    case 35:
  {
   HOUR = HOUR + C_twentyfive;
  }
  break;
    case 26:
    case 34:
  {
   HOUR = HOUR + C_twentysix;
  }
  break;
    case 27:
    case 33:
  {
   HOUR = HOUR + C_twentyseven;
  }
  break;
    case 28:
    case 32:
  {
   HOUR = HOUR + C_twentyeight;
  }
  break;
    case 29:
    case 31:
  {
   HOUR = HOUR + C_twentynine;
  }
  break;
    case 30:
  {
   HOUR = HOUR + C_thirty;
  }
  break;
 }

}
void Gen_Time() {
	  if (i_Time != DateTime.minute and (ntp_response_ok == true or manual_time_set == true) and date_ok == true) {
	  	//Serial.printf("HourFormat:%d\n", config.isFormat24h);
		    if (config.c_e_o == 1) {
		    	HOUR = C_E_O;
		    }
		    else {
		    	HOUR = "";
		    }
			if (DateTime.minute == 0) {
				HOUR = C_E_O;
				if (config.isFormat24h == 0 && DateTime.hour == 0) {
					temp_Hour = 24;
				}
				else {
				temp_Hour = DateTime.hour;
				}
				Gen_Hour();
				HOUR = HOUR + C_oclock;
			}
			else if (DateTime.minute >= 0 && DateTime.minute < 31) {
				if (config.isFormat24h == 0 && DateTime.hour == 0) {
					temp_Hour = 24;
				}
				else {
				temp_Hour = DateTime.hour;
				}
				Gen_Minute();
				HOUR = HOUR + C_past;
				Gen_Hour();
			}
			else if (DateTime.minute >= 31 && DateTime.minute <= 59) {
				if (DateTime.hour == 23 && config.isFormat24h == 1) {
					temp_Hour = 0;
				}
				else {
					temp_Hour = DateTime.hour + 1;
				}
				Gen_Minute();
				HOUR = HOUR + C_to;
				Gen_Hour();
			}
			//Gen_Minut();
			i_Time = DateTime.minute;
			clear_display();
			hour();
	    }
}



#endif /* EN_TIMEGEN_EN_H */
