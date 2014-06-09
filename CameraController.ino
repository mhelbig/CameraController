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
int numberOfTransitions=2;
int currentTransitionSelected=1;
float videoTimeSetting = 5;
float shootTimeSetting = 3600;
float startDelayTimeSetting =0;
int selectedMotionProfile = 0;

int videoFramesPerSecond = 30;

/////////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////////
#define MAX_NUMBER_OF_TRANSITIONS 5

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
  runSteppers();
}




