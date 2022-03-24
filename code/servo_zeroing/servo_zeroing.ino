// based on I2C Scanner written by Nick Gammon
// 

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int MAXPOS = 750;
int MINPOS = 400;

void setup() {
  Serial.begin (115200);

  // Leonardo: wait for serial port to connect
  while (!Serial) 
    {
    }

  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte address;
  
  Wire.begin();
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission (address);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (" (0x");
      Serial.print (address, HEX);
      Serial.println (")");
      break;
      } // end of good response
  } // end of for loop

  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, address);

  pwm.begin();
  
  pwm.setPWMFreq(120);


  for(int servonum=0; servonum<16; servonum++) {
    pwm.setPWM(servonum, 0, MAXPOS);
    delay(400);
  }

 delay(2000);
 
  for(int servonum=0; servonum<16; servonum++) {
    pwm.setPWM(servonum, 0, MINPOS);
    delay(400);
  }

}  // end of setup

void loop() {
  
  
  }
