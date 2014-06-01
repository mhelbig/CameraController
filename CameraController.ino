#include <MemoryFree.h>
#include <Wire.h>
#include <MenuSystem.h>
#include <Navchuk.h>
#include <spline.h>
#include <AccelStepper.h>

// Establish the input device
Navchuk nunchuk = Navchuk();

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
//  Serial.print("Free memory = "); Serial.println(freeMemory());
}


