#include <MemoryFree.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MenuSystem.h>
#include <Navchuk.h>
#include <spline.h>
#include <AccelStepper.h>

void setup()
{
  Serial.begin(9600);
  Serial.print("Free memory = "); Serial.println(freeMemory());
  initializeNavchuk();
  initializeLCD();
  initializeMenu();
  initializeSteppers();
  Serial.print("Free memory = "); Serial.println(freeMemory());
}

void loop() 
{
  navigationHandler();
}



