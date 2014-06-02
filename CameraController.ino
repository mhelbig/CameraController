#include <MemoryFree.h>
#include <Wire.h>
#include <MenuSystem.h>
#include <Navchuk.h>
#include <spline.h>
#include <AccelStepper.h>

// Establish the input device
Navchuk nunchuk = Navchuk();

/////////////////////////////////////////////////////////////////////////////////
// Global variables
/////////////////////////////////////////////////////////////////////////////////
// Timelapse Mode:
long videoTimeSetting = 30;
long shootTimeSetting = 3600;
int selectedMotionProfile = 0;

struct enumeratedMenuList
{
  char menuText[21];
  int value;
};

void setup()
{
  Serial.begin(9600);
  Serial.print("Free memory = "); 
  Serial.println(freeMemory());
  initializeNavchuk();
  initializeLCD();
  initializeMenu();
  initializeSteppers();

  Serial.print("Free memory = "); 
  Serial.println(freeMemory());
}

void loop() 
{
  navigationHandler();
  //  Serial.print("Free memory = "); Serial.println(freeMemory());
}




