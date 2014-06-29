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

/////////////////////////////////////////////////////////////////////////////////
// Global variables
/////////////////////////////////////////////////////////////////////////////////
// Timelapse Mode:
int selectedExposureIndex = 5;
int numberOfTransitions=1;
int currentTransitionSelected=1;
float shootTimeSetting = 3600;
float startDelayTimeSetting = 0;
int selectedMotionProfileIndex = 2;

// Settings menu:
int videoFramesPerSecondIndex = 2;
int shutterButtonTimeSetting = 100;
int cameraRecoveryTimeSetting = 200;
int motorSettleTimeSetting = 250;

struct enumeratedMenuList
{
  char menuText[21];
  int value;
};

enumeratedMenuList framesPerSecondList[]=
{
  { "120" ,120},
  { " 60" ,60},
  { " 30" ,30},
  { " 24" ,24}
};

enumeratedMenuList motionProfileList[]=
{
  { "Step  " ,0},  // corresponds to the spline.cpp setDegree() function
  { "Linear" ,1},
  { "Spline" ,11}  // we use the catmull spline type because it's easer to setup
};

enumeratedMenuList cameraExposureTime[]=
{
  { "       30"   ,30000},
  { "       25"   ,25000},
  { "       20"   ,20000},
  { "       15"   ,15000},
  { "       13"   ,13000},
  { "       10"   ,10000},
  { "        8"   ,8000},
  { "        6"   ,6000},
  { "        5"   ,5000},
  { "        4"   ,4000},
  { "      3.2"   ,3200},
  { "      3.0"   ,3000},
  { "      2.5"   ,2500},
  { "      2.0"   ,2000},
  { "      1.6"   ,1600},
  { "      1.5"   ,1500},
  { "      1.3"   ,1300},
  { "      1.0"   ,1000},
  { "      0.8"   ,800},
  { "      0.7"   ,700},
  { "      0.6"   ,600},
  { "      0.5"   ,500},
  { "      0.4"   ,400},
  { "      0.3"   ,300},
  { "      1/4"   ,250},
  { "Under 1/4"     ,0}
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




