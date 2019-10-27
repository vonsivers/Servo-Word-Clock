#ifndef TIMEGEN_DE_H
#define TIMEGEN_DE_H

void Gen_Hour() {
if ( config.isFormat24h == 0 && DateTime.hour > 12) {
	temp_Hour = temp_Hour - 12;
}
	switch (temp_Hour) {
	case 0: {
		HOUR = HOUR + C_null;
	}
		break;
	case 1: {
		HOUR = HOUR + C_ein;
	}
		break;
	case 2: {
		HOUR = HOUR + C_zwei;
	}
		break;
	case 3: {
		HOUR = HOUR + C_drei;
	}
		break;
	case 4: {
		HOUR = HOUR + C_vier;
	}
		break;
	case 5: {
		HOUR = HOUR + C_funf;
	}
		break;
	case 6: {
		HOUR = HOUR + C_sechs;
	}
		break;
	case 7: {
		HOUR = HOUR + C_sieben;
	}
		break;
	case 8: {
		HOUR = HOUR + C_acht;
	}
		break;
	case 9: {
		HOUR = HOUR + C_neun;
	}
		break;
	case 10: {
		HOUR = HOUR + C_zehn;
	}
		break;
	case 11: {
		HOUR = HOUR + C_elf;
	}
		break;
	case 12:
	case 24:
	{
		HOUR = HOUR + C_zwolf;
	}
		break;
	case 13: {
		HOUR = HOUR + C_dreizehn;
	}
		break;
	case 14: {
		HOUR = HOUR + C_vierzehn;
	}
		break;
	case 15: {
		HOUR = HOUR + C_funfzehn;
	}
		break;
	case 16: {
		HOUR = HOUR + C_sechzehn;
	}
		break;
	case 17: {
		HOUR = HOUR + C_siebzehn;
	}
		break;
	case 18: {
		HOUR = HOUR + C_achtzehn;
	}
		break;
	case 19: {
		HOUR = HOUR + C_neunzehn;
	}
		break;
	case 20: {
		HOUR = HOUR + C_zwanzig;
	}
		break;
	case 21: {
		HOUR = HOUR + C_einundzwanzig;
	}
		break;
	case 22: {
		HOUR = HOUR + C_zweiundzwanzig;
	}
		break;
	case 23: {
		HOUR = HOUR + C_dreiundzwanzig;
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
   HOUR = HOUR + C_ein;
  }
  break;
  case 2:
  case 58:
  {
   HOUR = HOUR + C_zwei;
  }
  break;
    case 3:
    case 57:
  {
   HOUR = HOUR + C_drei;
  }
  break;
    case 4:
    case 56:
  {
   HOUR = HOUR + C_vier;
  }
  break;
    case 5:
    case 55:
  {
   HOUR = HOUR + C_funf;
  }
  break;
    case 6:
    case 54:
  {
   HOUR = HOUR + C_sechs;
  }
  break;
    case 7:
    case 53:
  {
   HOUR = HOUR + C_sieben;
  }
  break;
    case 8:
    case 52:
  {
   HOUR = HOUR + C_acht;
  }
  break;
    case 9:
    case 51:
  {
   HOUR = HOUR + C_neun;
  }
  break;
    case 10:
    case 50:
  {
   HOUR = HOUR + C_zehn;
  }
  break;
    case 11:
    case 49:
  {
   HOUR = HOUR + C_elf;
  }
  break;
    case 12:
    case 48:
  {
   HOUR = HOUR + C_zwolf;
  }
  break;
    case 13:
    case 47:
  {
   HOUR = HOUR + C_dreizehn;
  }
  break;
    case 14:
    case 46:
  {
   HOUR = HOUR + C_vierzehn;
  }
  break;
    case 15:
    case 45:
  {
   HOUR = HOUR + C_viertel;
  }
  break;
    case 16:
    case 44:
  {
   HOUR = HOUR + C_sechzehn;
  }
  break;
    case 17:
    case 43:
  {
   HOUR = HOUR + C_siebzehn;
  }
  break;
    case 18:
    case 42:
  {
   HOUR = HOUR + C_achtzehn;
  }
  break;
    case 19:
    case 41:
  {
   HOUR = HOUR + C_neunzehn;
  }
  break;
    case 20:
    case 40:
  {
   HOUR = HOUR + C_zwanzig;
  }
  break;
    case 21:
    case 39:
  {
   HOUR = HOUR + C_einundzwanzig;
  }
  break;
    case 22:
    case 38:
  {
   HOUR = HOUR + C_zweiundzwanzig;
  }
  break;
    case 23:
    case 37:
  {
   HOUR = HOUR + C_dreiundzwanzig;
  }
  break;
    case 24:
    case 36:
  {
   HOUR = HOUR + C_vierundzwanzig;
  }
  break;
    case 25:
    case 35:
  {
   HOUR = HOUR + C_funfundzwanzig;
  }
  break;
    case 26:
    case 34:
  {
   HOUR = HOUR + C_sechsundzwanzig;
  }
  break;
    case 27:
    case 33:
  {
   HOUR = HOUR + C_siebenundzwanzig;
  }
  break;
    case 28:
    case 32:
  {
   HOUR = HOUR + C_achtundzwanzig;
  }
  break;
    case 29:
    case 31:
  {
   HOUR = HOUR + C_neunundzwanzig;
  }
  break;
    case 30:
  {
   HOUR = HOUR + C_halb;
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
				if (config.isFormat24h == 0 && DateTime.hour == 0) {
					temp_Hour = 24;
				}
				else {
				temp_Hour = DateTime.hour;
				}
				Gen_Hour();
				HOUR = HOUR + C_uhr;
			}
			else if (DateTime.minute >= 0 && DateTime.minute < 30) {
				if (config.isFormat24h == 0 && DateTime.hour == 0) {
					temp_Hour = 24;
				}
				else {
				temp_Hour = DateTime.hour;
				}
				Gen_Minute();
				HOUR = HOUR + C_nach;
				Gen_Hour();
			}
			else if (DateTime.minute == 30) {
				if (config.isFormat24h == 0 && DateTime.hour == 0) {
					temp_Hour = 24;
				}
				else {
				temp_Hour = DateTime.hour + 1;
				}
				//Gen_Minute();
				HOUR = HOUR + C_halb;
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
				HOUR = HOUR + C_vor;
				Gen_Hour();
			}
			i_Time = DateTime.minute;
			//Serial.println(HOUR);
			clear_display();
			hour();
	    }
}

#endif /* TIMEGEN_DE_H */
