#ifndef GLOBAL_H
#define GLOBAL_H

//WebServer server(80);							// The Webserver
DNSServer dnsServer;
AsyncWebServer server(80);

boolean firstStart = true;								// On firststart = true, NTP will try to get a valid time
boolean ntp_response_ok = false;
boolean manual_time_set = false;
String HOUR ="";
uint32_t chipID;
unsigned long delaytime=100;
int i_Time = 99;
int led_intensity = 8;
int temp_Hour = 0;
int WIFI_connected = false;
bool CFG_saved = false;
int AdminTimeOutCounter = 0;							// Counter for Disabling the AdminMode
WiFiUDP UDPNTPClient;											// NTP Client
volatile unsigned long UnixTimestamp = 0;	// GLOBALTIME  ( Will be set by NTP)
int cNTP_Update = 0;											// Counter for Updating the time via NTP
Ticker tkSecond;												  // Second - Timer for Updating Datetime Structure

uint8_t lastmin;                          // minute of last display update
bool updateDisplay = false;               // set to true if display needs update

//custom declarations
bool date_ok = false;
long absoluteActualTime, actualTime;
long  customWatchdog;                     // WatchDog to detect main loop blocking. There is a builtin WatchDog to the chip firmare not related to this one


struct strConfig {
  boolean dhcp;                         // 1 Byte - EEPROM 16
  boolean isDayLightSaving;             // 1 Byte - EEPROM 17
  long Update_Time_Via_NTP_Every;       // 4 Byte - EEPROM 18
  long timeZone;                        // 4 Byte - EEPROM 22
  byte  IP[4];                          // 4 Byte - EEPROM 32
  byte  Netmask[4];                     // 4 Byte - EEPROM 36
  byte  Gateway[4];                     // 4 Byte - EEPROM 40
  String ssid;                          // up to 32 Byte - EEPROM 64
  String password;                      // up to 32 Byte - EEPROM 96
  String ntpServerName;                 // up to 32 Byte - EEPROM 128
  String wcolor;                        // up to 32 Byte - EEPROM 160
  String bcolor;                        // up to 32 Byte - EEPROM 192
  String wcolormode;                    // up to 32 Byte - EEPROM 224
  String bcolormode;                    // up to 32 Byte - EEPROM 256
  uint8_t brightness;                   // 1 Byte - EEPROM 288
  String meffect;                       // up to 32 Byte - EEPROM 289
  String heffect;                       // up to 32 Byte - EEPROM 321
  String clockmode;                     // up to 32 Byte - EEPROM 353
  String dcolormode;                    // up to 32 Byte - EEPROM 385
  String dcolor;                        // up to 32 Byte - EEPROM 417
  String nightmode;                     // up to 32 Byte - EEPROM 449
  uint8_t wd_hour_start;                // 1 Byte - EEPROM 481
  uint8_t wd_minute_start;              // 1 Byte - EEPROM 482
  uint8_t wd_hour_end;                  // 1 Byte - EEPROM 483
  uint8_t wd_minute_end;                // 1 Byte - EEPROM 484
  uint8_t we_hour_start;                // 1 Byte - EEPROM 485
  uint8_t we_minute_start;              // 1 Byte - EEPROM 486
  uint8_t we_hour_end;                  // 1 Byte - EEPROM 487
  uint8_t we_minute_end;                // 1 Byte - EEPROM 488
} config;



//  Auxiliar function to handle EEPROM

void EEPROMWritelong(int address, long value){
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);

  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

long EEPROMReadlong(long address){
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);

  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

// Check the Values is between 0-255
boolean checkRange(String Value){
  if (Value.toInt() < 0 || Value.toInt() > 255)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void WriteStringToEEPROM(int beginaddress, String string){
  char  charBuf[string.length() + 1];
  string.toCharArray(charBuf, string.length() + 1);
  for (int t =  0; t < sizeof(charBuf); t++)
  {
    EEPROM.write(beginaddress + t, charBuf[t]);
  }
}

String  ReadStringFromEEPROM(int beginaddress){
  volatile byte counter = 0;
  char rChar;
  String retString = "";
  while (1)
  {
    rChar = EEPROM.read(beginaddress + counter);
    if (rChar == 0) break;
    if (counter > 31) break;
    counter++;
    retString.concat(rChar);

  }
  return retString;
}


void DefaultConfig() {
   uint64_t macAddress = ESP.getEfuseMac();
    uint64_t macAddressTrunc = macAddress << 40;
    chipID = macAddressTrunc >> 40;
    config.ssid = "ServoWordClock-" + String(chipID,HEX);       // SSID of access point
    config.password = "" ;   // password of access point
    config.dhcp = true;
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 100;                       // not used                     
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;   // not used   
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 254;   // not used
    config.ntpServerName = "pool.ntp.org"; 
    config.Update_Time_Via_NTP_Every =  3;
    config.timeZone = 10;
    config.isDayLightSaving = false;
    config.clockmode = "normal";
    config.brightness = 150;
    config.heffect = "effect1";
    config.meffect = "effect1";
    config.wcolormode = "random";
    config.wcolor = "#ff0000";
    config.bcolormode = "random";
    config.bcolor = "#ff0000";
    config.dcolormode = "random";
    config.dcolor = "#ff0000";
    config.nightmode = "silent";
    config.wd_hour_start = 0;
    config.wd_minute_start = 0;
    config.wd_hour_end = 0;
    config.wd_minute_end = 0;
    config.we_hour_start = 0;
    config.we_minute_start = 0;
    config.we_hour_end = 0;
    config.we_minute_end = 0;
}

void WriteConfig(){

  Serial.println("Writing Config");
  EEPROM.write(0, 'C');
  EEPROM.write(1, 'F');
  EEPROM.write(2, 'G');

  EEPROM.write(16, config.dhcp);
  EEPROM.write(17, config.isDayLightSaving);

  EEPROMWritelong(18, config.Update_Time_Via_NTP_Every); // 4 Byte
  EEPROMWritelong(22, config.timeZone); // 4 Byte

  EEPROM.write(32, config.IP[0]);
  EEPROM.write(33, config.IP[1]);
  EEPROM.write(34, config.IP[2]);
  EEPROM.write(35, config.IP[3]);

  EEPROM.write(36, config.Netmask[0]);
  EEPROM.write(37, config.Netmask[1]);
  EEPROM.write(38, config.Netmask[2]);
  EEPROM.write(39, config.Netmask[3]);

  EEPROM.write(40, config.Gateway[0]);
  EEPROM.write(41, config.Gateway[1]);
  EEPROM.write(42, config.Gateway[2]);
  EEPROM.write(43, config.Gateway[3]);

  WriteStringToEEPROM(64, config.ssid);
  WriteStringToEEPROM(96, config.password);
  WriteStringToEEPROM(128, config.ntpServerName);

  WriteStringToEEPROM(160, config.wcolor);
  WriteStringToEEPROM(192, config.bcolor);
  WriteStringToEEPROM(224, config.wcolormode);
  WriteStringToEEPROM(256, config.bcolormode);

  EEPROM.write(288, config.brightness);

  WriteStringToEEPROM(289, config.meffect);
  WriteStringToEEPROM(321, config.heffect);
  WriteStringToEEPROM(353, config.clockmode);

  WriteStringToEEPROM(385, config.dcolormode);
  WriteStringToEEPROM(417, config.dcolor);

  WriteStringToEEPROM(449, config.nightmode);
  EEPROM.write(481, config.wd_hour_start);
  EEPROM.write(482, config.wd_minute_start);
  EEPROM.write(483, config.wd_hour_end);
  EEPROM.write(484, config.wd_minute_end);
  EEPROM.write(485, config.we_hour_start);
  EEPROM.write(486, config.we_minute_start);
  EEPROM.write(487, config.we_hour_end);
  EEPROM.write(488, config.we_minute_end);

  EEPROM.commit();
}

void ClearConfig() {
  for (int i = 0 ; i < 512 ; i++) {
    EEPROM.write(i, 0);
  }
}

boolean ReadConfig(){
  Serial.println("Reading Configuration");
  if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
  {
    Serial.println("Configuration Found!");
    config.dhcp = 	EEPROM.read(16);
    config.isDayLightSaving = EEPROM.read(17);
    config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte
    config.timeZone = EEPROMReadlong(22); // 4 Byte
    config.IP[0] = EEPROM.read(32);
    config.IP[1] = EEPROM.read(33);
    config.IP[2] = EEPROM.read(34);
    config.IP[3] = EEPROM.read(35);
    config.Netmask[0] = EEPROM.read(36);
    config.Netmask[1] = EEPROM.read(37);
    config.Netmask[2] = EEPROM.read(38);
    config.Netmask[3] = EEPROM.read(39);
    config.Gateway[0] = EEPROM.read(40);
    config.Gateway[1] = EEPROM.read(41);
    config.Gateway[2] = EEPROM.read(42);
    config.Gateway[3] = EEPROM.read(43);
    config.ssid = ReadStringFromEEPROM(64);
    config.password = ReadStringFromEEPROM(96);
    config.ntpServerName = ReadStringFromEEPROM(128);
    config.wcolor = ReadStringFromEEPROM(160);
    config.bcolor = ReadStringFromEEPROM(192);
    config.wcolormode = ReadStringFromEEPROM(224);
    config.bcolormode = ReadStringFromEEPROM(256);
    config.brightness = EEPROM.read(288);
    config.meffect = ReadStringFromEEPROM(289);
    config.heffect = ReadStringFromEEPROM(321);
    config.clockmode = ReadStringFromEEPROM(353);
    config.dcolormode = ReadStringFromEEPROM(385);
    config.dcolor = ReadStringFromEEPROM(417);
    config.nightmode = ReadStringFromEEPROM(449);
    config.wd_hour_start = EEPROM.read(481);
    config.wd_minute_start = EEPROM.read(482);
    config.wd_hour_end = EEPROM.read(483);
    config.wd_minute_end = EEPROM.read(484);
    config.we_hour_start = EEPROM.read(485);
    config.we_minute_start = EEPROM.read(486);
    config.we_hour_end = EEPROM.read(487);
    config.we_minute_end = EEPROM.read(488);

    return true;

  }
  else
  {
    Serial.println("Configuration NOT FOUND!!!!");
    return false;
  }
}


void printConfig(){

  Serial.println("Printing Config");
  Serial.println("------------------");

  Serial.printf("DHCP:%d\n", config.dhcp);
  Serial.printf("DayLight:%d\n", config.isDayLightSaving);

  Serial.printf("NTP update every %ld min\n", config.Update_Time_Via_NTP_Every); // 4 Byte
  Serial.printf("Timezone %ld\n", config.timeZone); // 4 Byte

  Serial.printf("IP:%d.%d.%d.%d\n", config.IP[0],config.IP[1],config.IP[2],config.IP[3]);
  Serial.printf("Mask:%d.%d.%d.%d\n", config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3]);
  Serial.printf("Gateway:%d.%d.%d.%d\n", config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3]);

  Serial.printf("SSID:%s\n", config.ssid.c_str());
  Serial.printf("PWD:%s\n", config.password.c_str());
  Serial.printf("ntp ServerName:%s\n", config.ntpServerName.c_str());

  Serial.printf("Dot Color:%s\n", config.dcolor.c_str());
  Serial.printf("Word Color:%s\n", config.wcolor.c_str());
  Serial.printf("Background Color:%s\n", config.bcolor.c_str());
  Serial.printf("Dot Color Mode:%s\n", config.dcolormode.c_str());
  Serial.printf("Word Color Mode:%s\n", config.wcolormode.c_str());
  Serial.printf("Bkg Color Mode:%s\n", config.bcolormode.c_str());

  Serial.printf("Brightness %d\n", config.brightness); 

  Serial.printf("Minute Effect:%s\n", config.meffect.c_str());
  Serial.printf("Hour Effect:%s\n", config.heffect.c_str());
  Serial.printf("Clock Mode:%s\n", config.clockmode.c_str());

  Serial.printf("Night Mode:%s\n", config.nightmode.c_str());
  Serial.printf("weekdays hour start: %d\n", config.wd_hour_start);
  Serial.printf("weekdays minute start: %d\n", config.wd_minute_start);
  Serial.printf("weekdays hour end: %d\n", config.wd_hour_end);
  Serial.printf("weekdays minute end: %d\n", config.wd_minute_end);
  Serial.printf("weekend hour start: %d\n", config.we_hour_start);
  Serial.printf("weekend minute start: %d\n", config.we_minute_start);
  Serial.printf("weekend hour end: %d\n", config.we_hour_end);
  Serial.printf("weekend minute end: %d\n", config.we_minute_end);

  Serial.println("------------------");

}



String GetMacAddress(){
  uint8_t mac[6];
  char macStr[18] = {0};
  WiFi.macAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
  return  String(macStr);
}

String GetAPMacAddress(){
  uint8_t mac[6];
  char macStr[18] = {0};
  WiFi.softAPmacAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
  return  String(macStr);
}

// convert a single hex digit character to its integer value (from https://code.google.com/p/avr-netino/)
unsigned char h2int(char c){
  if (c >= '0' && c <= '9') {
    return ((unsigned char)c - '0');
  }
  if (c >= 'a' && c <= 'f') {
    return ((unsigned char)c - 'a' + 10);
  }
  if (c >= 'A' && c <= 'F') {
    return ((unsigned char)c - 'A' + 10);
  }
  return (0);
}

String urldecode(String input) // (based on https://code.google.com/p/avr-netino/)
{
  char c;
  String ret = "";

  for (byte t = 0; t < input.length(); t++)
  {
    c = input[t];
    if (c == '+') c = ' ';
    if (c == '%') {


      t++;
      c = input[t];
      t++;
      c = (h2int(c) << 4) | h2int(input[t]);
    }

    ret.concat(c);
  }
  return ret;

}


#endif
