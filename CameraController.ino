#include <MemoryFree.h>
#include <Wire.h>
#include <MenuSystem.h>
#include <Navchuk.h>
#include <spline.h>
#include <AccelStepper.h>
#include <TimerThree.h>
#include <NBtimer.h>

// Establish the input device
Navchuk nunchuk = Navchuk();

/////////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////////
#define MAX_NUMBER_OF_TRANSITIONS 8
#define EXPOSURE_TIME_BUFFER 100      // additional time (in mS) to wait after exposure before moving

/////////////////////////////////////////////////////////////////////////////////
// Global variables
/////////////////////////////////////////////////////////////////////////////////
// Timelapse Mode:
int selectedExposureIndex = 0;
int numberOfTransitions=1;
int currentTransitionSelected=1;
float shootTimeSetting = 3600;
float startDelayTimeSetting = 0;
int selectedMotionProfileIndex = 2;

// Settings menu:
int videoFramesPerSecond = 30;
long shutterPressTime = 100;

struct enumeratedMenuList
{
  char menuText[21];
  int value;
};

enumeratedMenuList motionProfileList[]=
{
  { "Step  " ,0},  // corresponds to the spline.cpp setDegree() function
  { "Linear" ,1},
  { "Spline" ,11}  // we use the catmull spline type because it's easer to setup
};

enumeratedMenuList cameraExposureTime[]=
{
  { "Under 1/4"     ,0},
  { "      1/4"   ,250},
  { "      0.3"   ,300},
  { "      0.4"   ,400},
  { "      0.5"   ,500},
  { "      0.6"   ,600},
  { "      0.7"   ,700},
  { "      0.8"   ,800},
  { "      1.0"   ,1000},
  { "      1.3"   ,1300},
  { "      1.5"   ,1500},
  { "      1.6"   ,1600},
  { "      2.0"   ,2000},
  { "      2.5"   ,2500},
  { "      3.0"   ,3000},
  { "      3.2"   ,3200},
  { "        4"   ,4000},
  { "        5"   ,5000},
  { "        6"   ,6000},
  { "        8"   ,8000},
  { "       10"   ,10000},
  { "       13"   ,13000},
  { "       15"   ,15000},
  { "       20"   ,20000},
  { "       25"   ,25000},
  { "       30"   ,30000}
};

//motor control and spline variables:
float frameNumber[MAX_NUMBER_OF_TRANSITIONS + 2] = {000,000,900,1200,1500,1800,1800};  // first and last values set tangent points

Spline XmotorSpline;
float XmotorSplinePoints_y[MAX_NUMBER_OF_TRANSITIONS + 2] = {0,0,0,0,0,0,0};           // motor positions
float XmotorPosition = 0;

Spline YmotorSpline;
float YmotorSplinePoints_y[MAX_NUMBER_OF_TRANSITIONS + 2] = {0,0,0,0,0,0,0};           // motor positions
float YmotorPosition = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("Free memory = "); 
  Serial.println(freeMemory());
  initializeShutterControl();
  initializeNavchuk();
  initializeLCD();
  initializeMenu();
  initializeSteppers();
  initializeStepperTimerISR();
  initializeSplines();

  Serial.print("Free memory = "); 
  Serial.println(freeMemory());
}

long cycleTime;

void loop() 
{
  navigationHandler();
  updateMotorPositions();
//  cycleTime = micros();

//  Serial.println(micros()-cycleTime);
}




