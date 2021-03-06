/*
 * ArduinoNunchukDemo.ino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Navchuk.h>

#define BAUDRATE 19200

#define I2C_ADDR    0x3F
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin,BACKLIGHT_PIN,POSITIVE);

int loopCount = 0;

Navchuk nunchuk = Navchuk();

void setup()
{
  Serial.begin(BAUDRATE);
  nunchuk.init();
  
  lcd.begin(20,4);               // initialize the lcd 

  lcd.home ();                   // go home
  lcd.print("Yo! Camera ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print("   Control!  ");      
}

void loop()
{
  nunchuk.update();

  lcd.setCursor ( 0, 2 );        // go to the next line
/*  lcd.print(nunchuk.analogDisplacementX, DEC);
  lcd.print(' ');
  lcd.print(nunchuk.analogDirectionX, DEC);
  lcd.print(' ');
  lcd.print(nunchuk.analogDisplacementY, DEC);
  lcd.print(' ');
  lcd.print(nunchuk.analogDirectionY, DEC);
  lcd.print(' ');
*/
  lcd.print(nunchuk.userInputState);
  lcd.print(' ');
  lcd.print(nunchuk.userInput);
  lcd.print(' ');

//  lcd.setCursor ( 0, 3 );        // go to the next line
//  lcd.print(nunchuk.accelX, DEC);
//  lcd.print(' ');
//  lcd.print(nunchuk.accelY, DEC);
//  lcd.print(' ');
//  lcd.print(nunchuk.accelZ, DEC);
//  lcd.print(' ');
  
  delay(250);
}
