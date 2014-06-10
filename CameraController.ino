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
float shootTimeSetting = 3600;
float startDelayTimeSetting =0;
int selectedMotionProfile = 0;

// Settings menu:
int videoFramesPerSecond = 30;


//motor control variables:
float frameNumber[7] = {000,000,900,1200,1500,1800,1800};  // first and last values set tangent points

Spline XmotorSpline;
float XmotorSplinePoints_y[7] = {0,0,0,0,0,0,0};                    // motor positions
float XmotorPosition = 0;

Spline YmotorSpline;
float YmotorSplinePoints_y[7] = {0,0,0,0,0,0,0};                    // motor positions
float YmotorPosition = 0;


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




