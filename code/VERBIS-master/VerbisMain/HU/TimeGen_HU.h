#ifndef HU_TIMEGEN_HU_H
#define HU_TIMEGEN_HU_H

//int temp_Hour = 0;
int temp_Minute = 0;

void Gen_Hour() {
 switch (temp_Hour) {
  case 0:
  case 12:
  case 24:
  {
   HOUR = HOUR + C_tizenketto;
  }
  break;
  case 1:
  case 13:
  {
   HOUR = HOUR + C_egy;
  }
  break;
    case 2:
    case 14:
  {
  if ((DateTime.minute >= 0 and DateTime.minute < 8) or (DateTime.minute > 52 and DateTime.minute < 60 )) {
	 HOUR = HOUR + C_ket;
     }
  else {
	 HOUR = HOUR + C_ketto;
     }
  }
  break;
    case 3:
    case 15:
  {
   HOUR = HOUR + C_harom;
  }
  break;
    case 4:
    case 16:
  {
   HOUR = HOUR + C_negy;
  }
  break;
    case 5:
    case 17:
  {
   HOUR = HOUR + C_ot;
  }
  break;
    case 6:
    case 18:
  {
   HOUR = HOUR + C_hat;
  }
  break;
    case 7:
    case 19:
  {
   HOUR = HOUR + C_het;
  }
  break;
    case 8:
    case 20:
  {
   HOUR = HOUR + C_nyolc;
  }
  break;
    case 9:
    case 21:
  {
   HOUR = HOUR + C_kilenc;
  }
  break;
    case 10:
    case 22:
  {
   HOUR = HOUR + C_tiz;
  }
  break;
    case 11:
    case 23:
  {
   HOUR = HOUR + C_tizenegy;
  }
  break;
 }
}

//==================

void Gen_Minute() {
 switch (temp_Minute) {
  case 1:
  {
   HOUR = HOUR + C_egy;
  }
  break;
  case 2:
  {
   HOUR = HOUR + C_ket;
  }
  break;
    case 3:
  {
   HOUR = HOUR + C_harom;
  }
  break;
    case 4:
  {
   HOUR = HOUR + C_negy;
  }
  break;
    case 5:
  {
   HOUR = HOUR + C_ot;
  }
  break;
    case 6:
  {
   HOUR = HOUR + C_hat;
  }
  break;
    case 7:
  {
   HOUR = HOUR + C_het;
  }
  break;
 }
}

//==================

void Gen_Time() {
  if (i_Time != DateTime.minute and (ntp_response_ok == true or manual_time_set == true) and date_ok == true) {
	  //clear_display();
	  HOUR = "";
	  switch (DateTime.minute) {
	  case 0:
	  {
	      temp_Hour = DateTime.hour;
	      Gen_Hour();
		  HOUR = HOUR + C_ora;
	  }
	  break;
	  case 1:
	  case 2:
	  case 3:
	  case 4:
	  case 5:
	  case 6:
	  case 7:
	  {
		  temp_Hour = DateTime.hour;
		  temp_Minute = DateTime.minute;
		  Gen_Hour();
		  HOUR = HOUR + C_ora + C_mult;
          Gen_Minute();
		  HOUR = HOUR + C_perccel;
	  }
	  break;
	  case 8:
	  case 9:
	  case 10:
	  case 11:
	  case 12:
	  case 13:
	  case 14:
	  {
		  temp_Minute = 15 - DateTime.minute;
		  temp_Hour = DateTime.hour + 1;
		  HOUR = HOUR + C_negyed;
		  Gen_Hour();
		  HOUR = HOUR + C_lesz;
		  Gen_Minute();
		  HOUR = HOUR + C_perc + C_mulva;
	  }
	  break;
	  case 15:
	  {
		  temp_Hour = DateTime.hour + 1;
		  HOUR = C_negyed;
		  Gen_Hour();
	  }
	  break;
	  case 16:
	  case 17:
	  case 18:
	  case 19:
	  case 20:
	  case 21:
	  case 22:
	  {
		  temp_Minute = DateTime.minute - 15;
		  temp_Hour = DateTime.hour + 1;
		  HOUR = HOUR + C_negyed;
		  Gen_Hour();
		  HOUR = HOUR+ C_mult;
		  Gen_Minute();
		  HOUR = HOUR + C_perccel;
	  }
	  break;
	  case 23:
	  case 24:
	  case 25:
	  case 26:
	  case 27:
	  case 28:
	  case 29:




	  {
		  temp_Minute = 30 - DateTime.minute;
		  temp_Hour = DateTime.hour + 1;
	  	  HOUR = HOUR + C_fel;
	  	  Gen_Hour();
	  	  HOUR = HOUR + C_lesz;
	  	  Gen_Minute();
	  	  HOUR = HOUR + C_perc + C_mulva;
	  }
	  	  break;
	  case 30:
	  {
		  temp_Hour = DateTime.hour + 1;
	  	  HOUR = HOUR + C_fel;
	  	  Gen_Hour();
	  }
	  	  break;
	  case 31:
	  case 32:
	  case 33:
	  case 34:
	  case 35:
	  case 36:
	  case 37:
	  {
		  temp_Minute = DateTime.minute - 30;
		  temp_Hour = DateTime.hour + 1;
	  	  HOUR = HOUR + C_fel;
	  	  Gen_Hour();
	  	  HOUR = HOUR + C_mult;
	  	  Gen_Minute();
	  	  HOUR = HOUR + C_perccel;
	  }
	  	  break;
	  case 38:
	  case 39:
	  case 40:
	  case 41:
	  case 42:
	  case 43:
	  case 44:
	  {
		  temp_Minute = 45 - DateTime.minute;
		  temp_Hour = DateTime.hour + 1;
	  	  HOUR = HOUR + C_haromnegyed;
	  	  Gen_Hour();
	  	  HOUR = HOUR + C_lesz;
	  	  Gen_Minute();
	  	  HOUR = HOUR + C_perc + C_mulva;
	  }
	  	  break;
	  case 45:
	  {
		  temp_Hour = DateTime.hour + 1;
	  	  HOUR = HOUR + C_haromnegyed;
	  	  Gen_Hour();
	  }
	  	  break;
	  case 46:
	  case 47:
	  case 48:
	  case 49:
	  case 50:
	  case 51:
	  case 52:
	  {
		  temp_Minute = DateTime.minute - 45;
		  temp_Hour = DateTime.hour + 1;
	  	  HOUR = HOUR + C_haromnegyed;
	  	  Gen_Hour();
	  	  HOUR = HOUR + C_mult;
	  	  Gen_Minute();
	  	  HOUR = HOUR + C_perccel;
	  }
	  	  break;
	  case 53:
	  case 54:
	  case 55:
	  case 56:
	  case 57:
	  case 58:
	  case 59:
	  {
		  temp_Minute = 60 - DateTime.minute;
		  temp_Hour = DateTime.hour + 1;
	  	  Gen_Hour();
	  	  HOUR = HOUR + C_ora + C_lesz;
	  	  Gen_Minute();
	  	  HOUR = HOUR + C_perc + C_mulva;
	  }
	  	  break;
	  }
	  i_Time = DateTime.minute;
	  clear_display();
	  hour();
  }
}

#endif /* HU_TIMEGEN_HU_H */
