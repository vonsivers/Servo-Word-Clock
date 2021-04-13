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
 
#ifndef LEDMATRIX_FUNCTIONS_H
#define LEDMATRIX_FUNCTIONS_H

#define FASTLED_INTERRUPT_RETRY_COUNT 1
//#define FASTLED_ALLOW_INTERRUPTS 0
#ifdef ESP32
  #define DATA_PIN    32
#elif defined(ESP8266)
  #define FASTLED_ESP8266_NODEMCU_PIN_ORDER     // use pin number as writen on the board
  #define DATA_PIN    3
#endif
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    114
CRGB leds[NUM_LEDS];
#define FRAMES_PER_SECOND  50

// #define OE_PIN  33  // PCA9685 output enable pin (active low)

// min/max position of servos
const uint16_t SERVOMIN = 400;
const uint16_t SERVOMAX = 700;

// definition of words (row,column), rows and columns start counting from 0 in upper left corner
//
uint8_t IT[][2] = { {0,0}, {0,1} };
uint8_t IS[][2] = { {0,3}, {0,4} };
uint8_t QUARTER[][2] = { {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8} };
uint8_t TWENTY[][2] = { {2,0}, {2,1}, {2,2}, {2,3}, {2,4}, {2,5} };
uint8_t FIVE_M[][2] = { {2,6}, {2,7}, {2,8}, {2,9} };
uint8_t HALF[][2] = { {3,0}, {3,1}, {3,2}, {3,3} };
uint8_t TEN_M[][2] = { {3,5}, {3,6}, {3,7} };
uint8_t TO[][2] = { {3,9}, {3,10} };
uint8_t PAST[][2] = { {4,0}, {4,1}, {4,2}, {4,3} };
uint8_t NINE[][2] = { {4,7}, {4,8}, {4,9}, {4,10} };
uint8_t ONE[][2] = { {5,0}, {5,1}, {5,2} };
uint8_t SIX[][2] = { {5,3}, {5,4}, {5,5} };
uint8_t THREE[][2] = { {5,6}, {5,7}, {5,8}, {5,9}, {5,10} };
uint8_t FOUR[][2] = { {6,0}, {6,1}, {6,2}, {6,3} };
uint8_t FIVE[][2] = { {6,4}, {6,5}, {6,6}, {6,7} };
uint8_t TWO[][2] = { {6,8}, {6,9}, {6,10} };
uint8_t EIGHT[][2] = { {7,0}, {7,1}, {7,2}, {7,3}, {7,4} };
uint8_t ELEVEN[][2] = { {7,5}, {7,6}, {7,7}, {7,8}, {7,9}, {7,10} };
uint8_t SEVEN[][2] = { {8,0}, {8,1}, {8,2}, {8,3}, {8,4} };
uint8_t TWELVE[][2] = { {8,5}, {8,6}, {8,7}, {8,8}, {8,9}, {8,10} };
uint8_t TEN[][2] = { {9,0}, {9,1}, {9,2} };
uint8_t OCLOCK[][2] = { {9,5}, {9,6}, {9,7}, {9,8}, {9,9}, {9,10} };

// WiFi symbol
//
uint8_t wifiSym0[][2] = { {9,5} };
uint8_t wifiSym1[][2] = { {8,3}, {7,4}, {7,5}, {7,6}, {8,7} };
uint8_t wifiSym2[][2] = { {6,2}, {5,3}, {4,4}, {4,5}, {4,6}, {5,7}, {6,8} };
uint8_t wifiSym3[][2] = { {4,1}, {3,2}, {2,3}, {2,4}, {2,5}, {2,6}, {2,7}, {3,8}, {4,9} }; 

// clock symbol
uint8_t clockSym[][2] = { {0,3}, {0,4}, {0,5}, {0,6}, {0,7}, 
                          {1,2}, {1,8}, 
                          {2,1}, {2,2}, {2,9}, 
                          {3,0}, {3,3}, {3,10}, 
                          {4,0}, {4,4}, {4,10}, 
                          {5,0}, {5,5}, {5,6}, {5,7}, {5,8}, {5,10}, 
                          {6,0}, {6,10},
                          {7,1}, {7,9},
                          {8,2}, {8,8},
                          {9,3}, {9,4}, {9,5}, {9,6}, {9,7} };

// clock circle + fixed arm
uint8_t clockCirc[][2] = { {0,3}, {0,4}, {0,5}, {0,6}, {0,7}, 
                          {1,2}, {1,8}, 
                          {2,1}, {2,9}, 
                          {3,0}, {3,10}, 
                          {4,0}, {4,10}, 
                          {5,0}, {5,5}, {5,6}, {5,7}, {5,8}, {5,10}, 
                          {6,0}, {6,10},
                          {7,1}, {7,9},
                          {8,2}, {8,8},
                          {9,3}, {9,4}, {9,5}, {9,6}, {9,7} };

// variable clock arm
uint8_t clockArm0[][2] = { {2,2}, {3,3}, {4,4} };
uint8_t clockArm1[][2] = { {1,5}, {2,5}, {3,5}, {4,5} };
uint8_t clockArm2[][2] = { {2,8}, {3,7}, {4,6} };
uint8_t clockArm3[][2] = { {5,9} };
uint8_t clockArm4[][2] = { {6,6}, {7,7} };
uint8_t clockArm5[][2] = { {6,5}, {7,5}, {8,5} };
uint8_t clockArm6[][2] = { {6,4}, {7,3} };

// setup servo drivers
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(&Wire, 0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(&Wire, 0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(&Wire, 0x42);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(&Wire, 0x43);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(&Wire, 0x44);
Adafruit_PWMServoDriver pwm6 = Adafruit_PWMServoDriver(&Wire, 0x45);
Adafruit_PWMServoDriver pwm7 = Adafruit_PWMServoDriver(&Wire, 0x46);
Adafruit_PWMServoDriver pwm8 = Adafruit_PWMServoDriver(&Wire, 0x47);
Adafruit_PWMServoDriver pwm9 = Adafruit_PWMServoDriver(&Wire, 0x48);
Adafruit_PWMServoDriver pwm10 = Adafruit_PWMServoDriver(&Wire, 0x49);
Adafruit_PWMServoDriver pwm11 = Adafruit_PWMServoDriver(&Wire, 0x4A);

uint8_t hue_b = 0; // color of background LEDs
uint8_t hue_w = 0; // color of words´
uint8_t hue_d = 0; // color of dots

uint16_t currentPos[11][11] = {SERVOMIN};  // current servo position
uint8_t usedLetters[11][11] = {0};  // letters in use
uint8_t currentHue[11][11] = {0};  // current hue

// delay (ms) between servo position update when moving slow/fast
uint16_t DELAY_slow = 5;   
uint16_t DELAY_fast = 1;

// current clockmode
String currentMode;

// counter for no Wifi animation
int wifiAnimation = 0;                   
long wifiMillis = 0;

// boolean for NTP animation
boolean ntpAnimation = 0;

// counter for fade in/out
uint8_t fade_counter = 0;
int fade_increment = 1;


// covert hex string to int
//
uint16_t strToHex(String input) {

  char hexValue[3];
  input.toCharArray(hexValue, 3);

  //Serial.print("char array: "); Serial.println(hexValue);

  int number = (int) strtol(hexValue, 0, 16);

  //byte tens = (hexValue[0] <= '9') ? hexValue[0] - '0' : hexValue[0] - '7';
  //byte ones = (hexValue[1] <= '9') ? hexValue[1] - '0' : hexValue[1] - '7';
  //byte number = (16 * tens) + ones;

  return number;
  
}


// convert hex color string to hue value
//
uint8_t hexToHue(String hex) {

  //Serial.print("input string: "); Serial.println(hex); 
  
  CHSV outputColor;
  CRGB inputColor;
  
  String red = hex.substring(1,3);
  String green = hex.substring(3,5);
  String blue = hex.substring(5);

  //Serial.print("r hex: "); Serial.println(red);
  //Serial.print("g hex: "); Serial.println(green);
  //Serial.print("b hex: "); Serial.println(blue);

  inputColor.r = (int) strToHex(red);
  inputColor.g = (int) strToHex(green);
  inputColor.b = (int) strToHex(blue);

  //Serial.print("r int: "); Serial.println(inputColor.r);
  //Serial.print("g int: "); Serial.println(inputColor.g);
  //Serial.print("b int: "); Serial.println(inputColor.b);
  
  outputColor = rgb2hsv_approximate(inputColor);

  //Serial.print("hue: "); Serial.println(outputColor.h);
  
  return outputColor.h;
  
}

// initialize servos
//
void initServos() {
  
  pwm1.begin();
  pwm1.setPWMFreq(120);
  delay(100);  
  pwm2.begin();
  pwm2.setPWMFreq(120);
  delay(100);   
  pwm3.begin();
  pwm3.setPWMFreq(120);
  delay(100);   
  pwm4.begin();
  pwm4.setPWMFreq(120);
  delay(100);   
  pwm5.begin();
  pwm5.setPWMFreq(120);
  delay(100);   
  pwm6.begin();
  pwm6.setPWMFreq(120); 
  delay(100);  
  pwm7.begin();
  pwm7.setPWMFreq(120);
  delay(100);   
  pwm8.begin();
  pwm8.setPWMFreq(120);
  delay(100); 
  pwm9.begin();
  pwm9.setPWMFreq(120);
  delay(100); 
  pwm10.begin();
  pwm10.setPWMFreq(120);
  delay(100); 
  pwm11.begin();
  pwm11.setPWMFreq(120);

}


// put servos to sleep
//
void sleepServos() {
  Serial.println("put servos to sleep");


// commented because it causes some servos to jump to another position
// see https://forums.adafruit.com/viewtopic.php?f=19&t=56256
// disabling servos via OE pin causes same issue
/*
  pwm1.sleep();
  pwm2.sleep();
  pwm3.sleep();
  pwm4.sleep();
  pwm5.sleep();
  pwm6.sleep();
  pwm7.sleep();
  pwm8.sleep();
  pwm9.sleep();
  pwm10.sleep();
  pwm11.sleep();
  */
  
}

// wake up servos
//
void wakeupServos() {
  Serial.println("wake up servos");

  /*
  pwm1.wakeup();
  pwm2.wakeup();
  pwm3.wakeup();
  pwm4.wakeup();
  pwm5.wakeup();
  pwm6.wakeup();
  pwm7.wakeup();
  pwm8.wakeup();
  pwm9.wakeup();
  pwm10.wakeup();
  pwm11.wakeup();
  */
  
}

// move servo to position
//
void moveServo(int row, int column, unsigned int pos) {

  // only move when current clock mode set to "normal"
  if(currentMode=="normal") {
    // check if position is within limits
    if (pos<=SERVOMAX && pos>=SERVOMIN) {

      if(row<10) {
      switch(column) {
        case 0: pwm11.setPWM(row,0,pos); break;
        case 1: pwm10.setPWM(row,0,pos); break;
        case 2: pwm9.setPWM(row,0,pos); break;
        case 3: pwm8.setPWM(row,0,pos); break;
        case 4: pwm7.setPWM(row,0,pos); break;
        case 5: pwm6.setPWM(row,0,pos); break;
        case 6: pwm5.setPWM(row,0,pos); break;
        case 7: pwm4.setPWM(row,0,pos); break;
        case 8: pwm3.setPWM(row,0,pos); break;
        case 9: pwm2.setPWM(row,0,pos); break;
        case 10: pwm1.setPWM(row,0,pos); break;
      }
      }
      else {
        switch(column) {
        case 0: pwm7.setPWM(15,0,pos); break;
        case 1: pwm6.setPWM(15,0,pos); break;
        case 2: pwm5.setPWM(15,0,pos); break;
        case 3: pwm4.setPWM(15,0,pos); break;
      }
    }
    currentPos[row][column] = pos;
    }
  }
}

// initialize matrix (move all servos to back, turn off LEDs)
//
void initMatrix() {
  Serial.println("resetting servos");
  FastLED.clear ();
  FastLED.show();
  for (int row=0; row<11; row++) {
    for (int column=0; column<11; column++) {
      moveServo(row,column,SERVOMIN);
      delay(150);
    }
  }
}

// initialize servo position variables
//
void initCurrentPos() {
  for (int row=0; row<11; row++) {
    for (int column=0; column<11; column++) {
      if(currentMode == "silent"){
        currentPos[row][column]=SERVOMAX;
      }
      else if(currentMode == "off") {
        currentPos[row][column]=SERVOMIN;
      }
    }
  }
}

// move all servos to front
//
void ServosToFront() {
  for(int pos=SERVOMIN+1; pos<=SERVOMAX; pos++) {
    for (int row=0; row<11; ++row) {
      for (int column=0; column<11; ++column) {
          if (currentPos[row][column]<SERVOMAX) {
            moveServo(row,column,pos);
          } 
      }
    }
    delay(DELAY_slow);
  }
}


// light up LED
//
void lightLED(int row, int column, int hue) {

  // only light LEDs if clock is not set to off
  if(currentMode!="off") {

  int i;
  // letters
  if(row<10) {
    i = 109-column*10-row;
    leds[i] = CHSV( hue, 255, 255);
  }
  // dots
  else {
    if(column<4) {
      i = 113 - column;
      leds[i] = CHSV( hue, 255, 255);
    }
  }
    
  currentHue[row][column] = hue;
  } 
    
}

void lightLEDBrightness(int row, int column, uint8_t hue, uint8_t brightness) {

  int i;
  // letters
  if(row<10) {
    i = 109-column*10-row;
    leds[i] = CHSV( hue, 255, brightness);
  }
  // dots
  else {
    if(column<4) {
      i = 113 - column;
      leds[i] = CHSV( hue, 255, brightness);
    }
  }
    
 currentHue[row][column] = hue; 
    
}

// make all LEDs black
//
void clearLEDs() {
  for (int row=0; row<11; ++row) {
      for (int column=0; column<11; ++column) {
        lightLEDBrightness(row,column,0,0);
      }
  }  
}

// show symbol on display
//
void lightupSym(uint8_t Sym[][2], int nLEDs, uint8_t hue) {

  for (int i = 0; i < nLEDs; i++) {
    lightLED(Sym[i][0],Sym[i][1],hue);
  }
  FastLED.show();
  
}

// show symbol on display
//
void lightupSymBrightness(uint8_t Sym[][2], int nLEDs, uint8_t hue, uint8_t brightness) {

  for (int i = 0; i < nLEDs; i++) {
    lightLEDBrightness(Sym[i][0],Sym[i][1],hue,brightness);
  }
  FastLED.show();
  
}


// show word on display
//
void lightup(uint8_t Word[][2], int nLetters, String effect) {
  
  // each word gets different random color
  if(config.wcolormode=="random") {
      do {    
      hue_w = random(256); 
      //Serial.print("hue_w="); Serial.println(hue_w);
      //Serial.print("abs(hue_w-hue_b)="); Serial.println(abs(hue_w-hue_b));
    } while(abs(hue_w-hue_b)<32 || (abs(hue_w-hue_b)>224));   // ensure that word color is different enough from bkg color
  }
  Serial.print("Hue words: "); Serial.println(hue_w);
  
  if (effect=="effect1") {    // typing effect (letters appear from left to right)
    for (int i = 0; i < nLetters; i++) {
        for (int pos=SERVOMIN; pos<=SERVOMAX; ++pos) {
          moveServo(Word[i][0],Word[i][1],pos);
          delay(DELAY_fast);
        }
      lightLED(Word[i][0],Word[i][1],hue_w);
      usedLetters[Word[i][0]][Word[i][1]]=1;
      FastLED.show();
    }
  }
  // words move slowly in, all letters simultaneously
  else if (effect=="effect2") { 
    double hueStep = (double)(hue_w - hue_b)/(double)(SERVOMAX-SERVOMIN);    
    double hue = (double)hue_b; 
    
    for (int pos=SERVOMIN; pos<=SERVOMAX; pos++) {
      for (int i = 0; i < nLetters; i++) {
        moveServo(Word[i][0],Word[i][1],pos);
        lightLED(Word[i][0],Word[i][1],(int)hue);
        usedLetters[Word[i][0]][Word[i][1]]=1;
      }
    hue += hueStep;
    FastLED.show();
    delay(DELAY_slow);
    }
   }
   // for other effects just mark letters which are needed to display time
   else {
    for (int i = 0; i < nLetters; i++) {
      usedLetters[Word[i][0]][Word[i][1]]=1;
    }
   }
}

// move all letters simultaneously to back, light all LEDs with background color
//
void LettersToBack() {

  for(int pos=SERVOMAX-1; pos>=SERVOMIN; pos--) {
    for (int row=0; row<11; ++row) {
      for (int column=0; column<11; ++column) {
          uint8_t hue = currentHue[row][column];
          double hueStep = (double)(hue_b - hue)/(double)(pos-SERVOMIN+1);
          hue += hueStep;
          lightLED(row,column,(int)hue);
          if (currentPos[row][column]>SERVOMIN) {
            moveServo(row,column,pos);
          }
      }
    }
    FastLED.show();
    delay(DELAY_slow);
  }
  
}


// move all letters simultaneously to front, light all LEDs with word color
void LettersToFront() {
  
  for(int pos=SERVOMIN+1; pos<=SERVOMAX; pos++) {
    for (int row=0; row<11; ++row) {
      for (int column=0; column<11; ++column) {
          uint8_t hue = currentHue[row][column];
          double hueStep = (double)(hue_w - hue)/(double)(SERVOMAX-pos+1);
          hue += hueStep;
          lightLED(row,column,(int)hue);
          if (currentPos[row][column]<SERVOMAX) {
            moveServo(row,column,pos);
          } 
      }
    }
    FastLED.show();
    delay(DELAY_slow);
  }
}



// move all letters to random position and assign random color
//
void LettersToRandom() {
  for (int row=0; row<11; ++row) {
    for (int column=0; column<11; ++column) {
      moveServo(row,column,random(SERVOMIN,SERVOMAX));
      lightLED(row,column,random(256));
      FastLED.show();
      delay(random(50,250));
    }
  }
}


// show hours on display
//
void setHours(byte c_hour, String effect) {
    switch (c_hour) {
                case 0:
                case 12:
                case 24:
                    lightup(TWELVE,sizeof(TWELVE)/sizeof(TWELVE[0]),effect);
                    break;
                case 1:
                case 13:
                    lightup(ONE,sizeof(ONE)/sizeof(ONE[0]),effect);
                    break;
                case 2:
                case 14:
                   lightup(TWO,sizeof(TWO)/sizeof(TWO[0]),effect);
                    break;
                case 3:
                case 15:
                    lightup(THREE,sizeof(THREE)/sizeof(THREE[0]),effect);
                    break;
                case 4:
                case 16:
                    lightup(FOUR,sizeof(FOUR)/sizeof(FOUR[0]),effect);
                    break;
                case 5:
                case 17:
                    lightup(FIVE,sizeof(FIVE)/sizeof(FIVE[0]),effect);
                    break;
                case 6:
                case 18:
                    lightup(SIX,sizeof(SIX)/sizeof(SIX[0]),effect);
                    break;
                case 7:
                case 19:
                    lightup(SEVEN,sizeof(SEVEN)/sizeof(SEVEN[0]),effect);
                    break;
                case 8:
                case 20:
                    lightup(EIGHT,sizeof(EIGHT)/sizeof(EIGHT[0]),effect);
                    break;
                case 9:
                case 21:
                    lightup(NINE,sizeof(NINE)/sizeof(NINE[0]),effect);
                    break;
                case 10:
                case 22:
                    lightup(TEN,sizeof(TEN)/sizeof(TEN[0]),effect);
                    break;
                case 11:
                case 23:
                    lightup(ELEVEN,sizeof(ELEVEN)/sizeof(ELEVEN[0]),effect);
                    break;
            }            
}


// update dots showing minutes
//
void updateMinutes(String effect) {
  
  Serial.println("updating dots");
  
  if(config.dcolormode=="fixed") {
   hue_d = hexToHue(config.dcolor);
  }
  else if(config.dcolormode=="random") {
    do {    
      hue_d = random(256); 
    } while(abs(hue_d-hue_b)<32 || (abs(hue_d-hue_b)>224));   // ensure that dot color is different enough from bkg color
  }
  
  int ndots = (DateTime.minute % 5);

  if(effect=="effect1") {
    for (int i=0; i<ndots; ++i) {
      for (int pos=currentPos[10][i]; pos<=SERVOMAX; ++pos) {
        moveServo(10,i,pos);
        delay(DELAY_slow);
      }
      lightLED(10,i,hue_d);
      FastLED.show();
      usedLetters[10][i]=1;
    }
  }
  else if (effect=="effect2") {
    double hueStep = (double)(hue_d - hue_b)/(double)(SERVOMAX-SERVOMIN);    
    double hue = (double)hue_b;
    for (int pos=SERVOMIN; pos<=SERVOMAX; ++pos) {
      for (int i=0; i<ndots; ++i) {
        moveServo(10,i,pos);
        lightLED(10,i,(int)hue);
        usedLetters[10][i]=1;
      }
      hue += hueStep;
      FastLED.show();
      delay(DELAY_slow);
    }
  }
  else {
    for (int i=0; i<ndots; ++i) {
      usedLetters[10][i]=1;
    }
  }
  
}


// shows time on clock
//
void updateTime() {

  Serial.println("updating words");
  // reset used letters variable
  for(int row=0; row<11; row++) {
    for(int column=0; column<11; column++) {
      usedLetters[row][column]=0;
    }
  }

  // select effect
  // "effect1": letters move in from back one by one 
  // "effect2": letters of every word move in simultaneously from back, 
  // "effect3": all letters move back simultaneously from front
  // "effect4": letters move first to random position then simultaneously to final position
  // "random": random effect

  String effects[4] = {"effect1", "effect2", "effect3", "effect4"};
  String effect;
  
  // check if full hour
  if(DateTime.minute / 5 == 0) {
    effect = config.heffect;
  }
  else {
    effect = config.meffect;
  }
  if(effect=="random") {
    effect = effects[random(4)];
  }

  // set LED brightness
  FastLED.setBrightness(config.brightness);

  // choose background color
  if(config.bcolormode=="fixed") {
      hue_b = hexToHue(config.bcolor);
  }
  else if(config.bcolormode=="random") {
    hue_b = random(256);
  }
  Serial.print("Hue background: "); Serial.println(hue_b);

  // choose word color
  if(config.wcolormode=="fixed") {
      hue_w = hexToHue(config.wcolor);
  }
  else {
    do {    
      hue_w = random(256); 
    } while(abs(hue_w-hue_b)<32 || (abs(hue_w-hue_b)>224));   // ensure that word color is different enough from bkg color
  }
  Serial.print("Hue words: "); Serial.println(hue_w);

  // move servos to front if mode was changed to silent
  if(config.clockmode=="silent" && currentMode!="silent") {
    Serial.println("clock mode switched to silent");
    ServosToFront();
    delay(500);
    sleepServos();
  }
  // move servos to back and switch off LEDs if mode was changed to off
  else if(config.clockmode=="off" && currentMode!="off") {
    Serial.println("clock mode switched to off");
    LettersToBack();
    FastLED.clear();
    FastLED.show();
    delay(500);
    sleepServos();
  }
  // initialize servos if mode changed to normal
  else if(config.clockmode=="normal" && currentMode!="normal") {
    Serial.println("clock mode switched to normal");
    wakeupServos();
  }

  // change current clock mode
  currentMode = config.clockmode;

  // move all letters to front 
  if(effect=="effect3") {
   LettersToFront(); 
  }
  // move letters to random position 
  else if(effect=="effect4") {
    LettersToRandom();
  }
  // move letters to back
  else {
    LettersToBack();
  }
  
   // light up "IT IS" first
  lightup(IT,sizeof(IT)/sizeof(IT[0]),effect);
  lightup(IS,sizeof(IS)/sizeof(IS[0]),effect);

  // show minutes and hours
  switch (DateTime.minute / 5) {
                case 0:
                    // full hour
                      setHours(DateTime.hour,effect);
                      lightup(OCLOCK,sizeof(OCLOCK)/sizeof(OCLOCK[0]),effect);
                    break;
                case 1:
                    // 5 past
                      lightup(FIVE_M,sizeof(FIVE_M)/sizeof(FIVE_M[0]),effect);
                      lightup(PAST,sizeof(PAST)/sizeof(PAST[0]),effect);
                      setHours(DateTime.hour,effect);
                    break;
                case 2:
                    // 10 past
                      lightup(TEN_M,sizeof(TEN_M)/sizeof(TEN_M[0]),effect);
                      lightup(PAST,sizeof(PAST)/sizeof(PAST[0]),effect);
                      setHours(DateTime.hour,effect);
                    break;
                case 3:
                    // quarter past
                      lightup(QUARTER,sizeof(QUARTER)/sizeof(QUARTER[0]),effect);
                      lightup(PAST,sizeof(PAST)/sizeof(PAST[0]),effect);
                      setHours(DateTime.hour,effect);
                    break;
                case 4:
                    // 20 past
                    lightup(TWENTY,sizeof(TWENTY)/sizeof(TWENTY[0]),effect);
                      lightup(PAST,sizeof(PAST)/sizeof(PAST[0]),effect);
                      setHours(DateTime.hour,effect);
                    break;
                case 5:
                    // 25 past
                 lightup(TWENTY,sizeof(TWENTY)/sizeof(TWENTY[0]),effect);
                      lightup(FIVE_M,sizeof(FIVE_M)/sizeof(FIVE_M[0]),effect);
                      lightup(PAST,sizeof(PAST)/sizeof(PAST[0]),effect);
                      setHours(DateTime.hour,effect);
                    break;
                case 6:
                    // half past
                      lightup(HALF,sizeof(HALF)/sizeof(HALF[0]),effect);
                      lightup(PAST,sizeof(PAST)/sizeof(PAST[0]),effect);
                      setHours(DateTime.hour,effect);
                    break;
                case 7:
                    // 25 to
                      lightup(TWENTY,sizeof(TWENTY)/sizeof(TWENTY[0]),effect);
                      lightup(FIVE_M,sizeof(FIVE_M)/sizeof(FIVE_M[0]),effect);
                      lightup(TO,sizeof(TO)/sizeof(TO[0]),effect);
                      setHours(DateTime.hour + 1,effect);
                    break;
                case 8:
                    // 20 to
                      lightup(TWENTY,sizeof(TWENTY)/sizeof(TWENTY[0]),effect);
                      lightup(TO,sizeof(TO)/sizeof(TO[0]),effect);
                      setHours(DateTime.hour + 1,effect);
                    break;
                case 9:
                    // 15 to
                      lightup(QUARTER,sizeof(QUARTER)/sizeof(QUARTER[0]),effect);
                      lightup(TO,sizeof(TO)/sizeof(TO[0]),effect);
                      setHours(DateTime.hour + 1,effect);
                    break;
                case 10:
                      lightup(TEN_M,sizeof(TEN_M)/sizeof(TEN_M[0]),effect);
                      lightup(TO,sizeof(TO)/sizeof(TO[0]),effect);
                      setHours(DateTime.hour + 1,effect);
                    break;
                case 11:
                    // 5 to
                      lightup(FIVE_M,sizeof(FIVE_M)/sizeof(FIVE_M[0]),effect);
                      lightup(TO,sizeof(TO)/sizeof(TO[0]),effect);
                      setHours(DateTime.hour + 1,effect);
                    break;
            }
            updateMinutes(effect);

            // for fade out effect move all background LEDs to back
            if(effect=="effect3") {
              //double hueStep = (double)(hue_b - hue_w)/(double)(SERVOMAX-SERVOMIN);    
              //double hue = (double)hue_w;
              for(int pos=SERVOMAX-1; pos>=SERVOMIN; pos--) {
                for(int row=0; row<11; row++) {
                   for(int column=0; column<11; column++) {    
                    // if LED is not used for words
                    if(usedLetters[row][column]==0) {
                      uint8_t hue = currentHue[row][column];
                      double hueStep = (double)(hue_b - hue)/(double)(pos-SERVOMIN+1);
                      hue += hueStep;
                      moveServo(row,column,pos);
                      lightLED(row,column,hue);
                    }
                  }
                }
                FastLED.show();
                delay(DELAY_slow);  
              }
            }
            // for color mix effect simultanously move all letters to final position
            else if(effect=="effect4") {
              int n = 0; // number of letters that reached final position
              while (n<121) {
                n = 0;
                for (int row=0; row<11; ++row) {
                  for (int column=0; column<11; ++column) {
                    unsigned int pos = currentPos[row][column];
                    uint8_t hue = currentHue[row][column];
                    // check if letter needs to be moved to front
                    if(usedLetters[row][column]) {          
                      // servos only move when clock mode set to normal
                      if(currentMode == "normal") { 
                        double hueStep = (double)(hue_w - hue)/(double)(SERVOMAX-pos);
                        if(pos<SERVOMAX) {
                          pos++;
                          hue += hueStep;
                          moveServo(row,column,pos);
                          lightLED(row,column,hue);
                        }
                        else {
                          lightLED(row,column,hue_w); // ensure correct color
                          n++;    // letter in final position
                        }
                      }
                      // in silent mode just change hue to final value
                      else {
                        if(hue!=hue_w) {
                          hue++;
                          //Serial.print("incrementing hue of word letter: "); Serial.println(hue);
                          lightLED(row,column,hue);
                        }
                        else {
                          lightLED(row,column,hue_w); // ensure correct color
                          n++;    // letter in final position
                          //Serial.print("letters in final position: "); Serial.println(n);
                        }
                      }
                    }
                    // letters which go to back
                    else {
                      // servos only move when clock mode set to normal
                      if(currentMode == "normal") {
                        double hueStep = (double)(hue_b - hue)/(double)(pos-SERVOMIN);
                        if(pos>SERVOMIN) {
                          pos--;
                          hue += hueStep;
                          moveServo(row,column,pos);
                          lightLED(row,column,hue);
                        }
                        else {
                          lightLED(row,column,hue_b); // ensure correct color
                          n++;    // letter in final position
                        }
                      }
                      // in silent mode just change hue to final value
                      else {
                        if(hue!=hue_b) {
                          hue++;
                          //Serial.print("incrementing hue of bkg letter: "); Serial.println(hue);
                          lightLED(row,column,hue);
                        }
                        else {
                          lightLED(row,column,hue_b); // ensure correct color
                          n++;    // letter in final position
                          //Serial.print("letters in final position: "); Serial.println(n);
                        }
                      }
                    }
                  }
                }
                FastLED.show();
                delay(DELAY_slow);
              }
            }
}


// update background color in color cycle mode
//
void updateBkgColor() {
  //Serial.println("updating bkg color");
  hue_b++;
  for (int row=0; row<11; ++row) {
    for (int column=0; column<11; ++column) {
      // check if letter is displaying time
      if(!usedLetters[row][column]) {
        lightLED(row,column,hue_b);
      }
    }
  }
  FastLED.show();  
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND); 
}


// show "no wifi" animation
//
void LED_no_wifi() {

  uint8_t hue = 32;

  if(millis()-wifiMillis>1000) {
    // add another "wave" each second
   switch(wifiAnimation) {
    case 0: FastLED.clear(); lightupSym(wifiSym0,sizeof(wifiSym0)/sizeof(wifiSym0[0]),hue); break;
    case 1: lightupSym(wifiSym1,sizeof(wifiSym1)/sizeof(wifiSym1[0]),hue); break;
    case 2: lightupSym(wifiSym2,sizeof(wifiSym2)/sizeof(wifiSym2[0]),hue); break;
    case 3: lightupSym(wifiSym3,sizeof(wifiSym3)/sizeof(wifiSym3[0]),hue); break;
   }
   if(wifiAnimation==3) {
    wifiAnimation = 0;
   }
   else {
    wifiAnimation++;
   }
   wifiMillis = millis();
  }

     
}

// show "no NTP" animation
//
void LED_no_ntp() {

  if (!ntpAnimation) {
  uint8_t hue = 96;
  FastLED.clear();
  lightupSym(clockSym,sizeof(clockSym)/sizeof(clockSym[0]),hue);
  FastLED.show();
  ntpAnimation = true;
  }

  /*
  lightupSymBrightness(clockSym,sizeof(clockSym)/sizeof(clockSym[0]),hue,fade_counter);
    fade_counter += fade_increment;

            if(fade_counter==255) {
              fade_increment = -10;   
            }
            else if(fade_counter==0) {
              fade_increment = 10;
            }
            // insert a delay to keep the framerate modest
            FastLED.delay(1000/FRAMES_PER_SECOND);
            clearLEDs();
            FastLED.show();
*/
  /*
if(millis()-ntpMillis>1000) {
  FastLED.clear();
    // change arm every second
   switch(ntpAnimation) {
    case 0: 
      lightupSym(clockCirc,sizeof(clockCirc)/sizeof(clockCirc[0]),hue); 
      lightupSym(clockArm0,sizeof(clockArm0)/sizeof(clockArm0[0]),hue); 
      break;
    case 1: 
      lightupSym(clockCirc,sizeof(clockCirc)/sizeof(clockCirc[0]),hue); 
      lightupSym(clockArm1,sizeof(clockArm1)/sizeof(clockArm1[0]),hue); 
      break;
    case 2: 
      lightupSym(clockCirc,sizeof(clockCirc)/sizeof(clockCirc[0]),hue); 
      lightupSym(clockArm2,sizeof(clockArm2)/sizeof(clockArm2[0]),hue); 
      break;
    case 3: 
      lightupSym(clockCirc,sizeof(clockCirc)/sizeof(clockCirc[0]),hue); 
      lightupSym(clockArm3,sizeof(clockArm3)/sizeof(clockArm3[0]),hue); 
      break;
    case 4: 
      lightupSym(clockCirc,sizeof(clockCirc)/sizeof(clockCirc[0]),hue); 
      lightupSym(clockArm4,sizeof(clockArm4)/sizeof(clockArm4[0]),hue); 
      break;
    case 5: 
      lightupSym(clockCirc,sizeof(clockCirc)/sizeof(clockCirc[0]),hue); 
      lightupSym(clockArm5,sizeof(clockArm5)/sizeof(clockArm5[0]),hue); 
      break;
    case 6: 
      lightupSym(clockCirc,sizeof(clockCirc)/sizeof(clockCirc[0]),hue); 
      lightupSym(clockArm3,sizeof(clockArm6)/sizeof(clockArm6[0]),hue); 
      break;
   }
   if(ntpAnimation==6) {
    ntpAnimation = 0;
   }
   else {
    ntpAnimation++;
   }
   ntpMillis = millis();
   FastLED.clear();
  }  
  */
}




// update dot showing seconds
//
/*
void updateSeconds() {
  unsigned long currentMillis = millis();
  unsigned long milliseconds = (currentMillis - lastMillis) % 60000;
  //unsigned long periodMillis = currentMillis - lastMillis;
  //unsigned long milliseconds;
  int ndots = (DateTime.minute % 5);
    unsigned int servomin = pgm_read_word_near(SERVOMIN_CAL + servonum(11,ndots+1));
    unsigned int servomax = pgm_read_word_near(SERVOMAX_CAL + servonum(11,ndots+1));
    //if (periodMillis<1000) {
      //milliseconds = second(c_time)*1000 + periodMillis;
    //}
    //else {
      //milliseconds = second(c_time)*1000;
    //}
    unsigned int pos = map(milliseconds,0,60000,servomin,servomax);
    uint8_t currentHue = map(milliseconds,0,60000,gHue,hueDots);
    moveServo(11,ndots+1,pos);
    lightLED(11,ndots+1,currentHue,255,255);
    //lastMillis = currentMillis;
    FastLED.show();
  //delay(10);
}
*/



// test all LEDs
//
void testLEDs() {
  for (int row=0; row<11; row++) {
    for (int column=0; column<11; column++) {
      lightLED(row,column,0);
      FastLED.show();
      delay(100);
    }
  }

  for (int row=0; row<11; row++) {
    for (int column=0; column<11; column++) {
      lightLED(row,column,96);
      FastLED.show();
      delay(100);
    }
  }

 for (int row=0; row<11; row++) {
    for (int column=0; column<11; column++) {
      lightLED(row,column,160);
      FastLED.show();
      delay(100);
    }
  }
 
}

// test all servos
//
void testServos() {
  
  // first move all letters to back and turn off LEDs
  //initMatrix();
  
  // letters
  for (int row=0; row<11; row++) {
    for (int column=0; column<11; column++) {
      moveServo(row,column,SERVOMAX);
      lightLED(row,column,96);
      FastLED.show();
      delay(150);
    }
  }
  
}






#endif /* LEDMATRIX_FUNCTIONS_H */
