#include <MemoryFree.h>
#include <Wire.h>
#include <MenuSystem.h>
#include <Navchuk.h>
#include <spline.h>
#include <AccelStepper.h>
#include <TimerThree.h>
#include <NBtimer.h>
#include <EEPROMex.h>

// Establish the input device
Navchuk nunchuk = Navchuk();

/////////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////////
#define MAX_NUMBER_OF_TRANSITIONS 5
#define OSCILLATOR_COMPENSATION 1.05  // Use this to correct for long exposure time sync issues
                                      // between the Arduino clock and the camera 1.0 = 100%

/////////////////////////////////////////////////////////////////////////////////
// Global variables
/////////////////////////////////////////////////////////////////////////////////
// Timelapse Mode:
int selectedExposureIndex     = 21;
int numberOfTransitions       = 1;
int currentTransitionSelected = 1;
float shootTimeSetting        = 600;
float startDelayTimeSetting   = 0;
float ZmotorMinPosition       = 0;
float ZmotorMaxPosition       = 0;
float DmotorMinPosition       = 0;
float DmotorMaxPosition       = 0;
int   RmotorIncrementValue    = 0;

// Video Pan Mode:
float panTimeSetting          = 30;   // desired pan time setting
float panTime                 = 0;    // pan time during pans
float panOvershootTime        = 3;    // additional time and panning added before and after the pan shoot sequence
float panRevsSetting          = 1;    // desired number of pan rotations
float XmotorPanHomePosition   = 0;    // start position for pan sequences
float YmotorPanHomePosition   = 0;    // tilt position held during pans
float XmotorPanPosition       = 0;    // calculated motor position

// Non-Volatile Settings:  (values are loaded from EEPROM on startup)
int backlightTimeIndex;
int lensDefoggerPWMsetting;
int lensDefoggerModeIndex;
int shutterButtonTimeSetting;
int postShootTimeDelaySetting;
int cameraRecoveryTimeSetting;
int motorSettleTimeSetting;
int videoFramesPerSecondIndex;
int selectedMotionProfileIndex;

int selectedXmotorInvertIndex;
int selectedXmotorEnableIndex;
unsigned int XmotorStepsPerRev;

int selectedYmotorInvertIndex;
int selectedYmotorEnableIndex;

int selectedZmotorInvertIndex;
int selectedZmotorEnableIndex;

int selectedDmotorInvertIndex;
int selectedDmotorEnableIndex;

int selectedRmotorInvertIndex;
int selectedRmotorEnableIndex;
unsigned int RmotorStepsPerRev;

//motor control and spline variables:
float frameNumber[MAX_NUMBER_OF_TRANSITIONS + 2] = {000,000,900,1200,1500,1800,1800};  // first and last values set tangent points

Spline XmotorSpline;
float XmotorSplinePoints_y[MAX_NUMBER_OF_TRANSITIONS + 2] = {0,0,0,0,0,0,0};           // motor positions
float XmotorPosition = 0;

Spline YmotorSpline;
float YmotorSplinePoints_y[MAX_NUMBER_OF_TRANSITIONS + 2] = {0,0,0,0,0,0,0};           // motor positions
float YmotorPosition = 0;

Spline ZmotorSpline;
float ZmotorSplinePoints_y[MAX_NUMBER_OF_TRANSITIONS + 2] = {0,0,0,0,0,0,0};           // motor positions
float ZmotorPosition = 0;

Spline DmotorSpline;
float DmotorSplinePoints_y[MAX_NUMBER_OF_TRANSITIONS + 2] = {0,0,0,0,0,0,0};           // motor positions
float DmotorPosition = 0;

float RmotorPosition = 0;                                                              // Rotation does not use a spline function, just an increment each frame

/////////////////////////////////////////////////////////////////////////////////
// Enumerated menu lists
/////////////////////////////////////////////////////////////////////////////////
struct enumeratedMenuList
{
  char menuText[21];
  int value;
};

enumeratedMenuList backlightTimeList[]=
{
  { "5 minutes      " ,300}, // Generally used for development or AC powered setups
  { "30 seconds     " ,30},  // Generally used for day time
  { "2 seconds      " ,2}    // Generally used for night mode to minimize eye strain going from menus to camera
};

enumeratedMenuList lensDefoggerModeList[]=
{
  { "Always Off     " ,0},  // Never turn on the defogger
  { "Always On      " ,1},  // Always have on the defogger
  { "On During Shoot" ,2}   // Only turn on the defogger during the shoot sequence
};

enumeratedMenuList framesPerSecondList[]=
{
  { "120" ,120},
  { " 60" ,60},
  { " 30" ,30},
  { " 24" ,24}
};

enumeratedMenuList motorInvertList[]=
{
  { "Normal" ,1},
  { "Invert" ,-1}
};

enumeratedMenuList motorEnableList[]=
{
  { "During Moves" ,0},
  { "During Shoot" ,1},
  { "Always On   " ,2}
};

enumeratedMenuList motionProfileList[]=
{
  { "Step  " ,0},  // corresponds to the spline.cpp setDegree() function
  { "Linear" ,1},
  { "Spline" ,11}  // we use the catmull spline type because it's easer to setup
};

enumeratedMenuList cameraExposureTime[]=
{
  { "       30"   ,32000},
  { "       25"   ,25398},
  { "       20"   ,20159},
  { "       15"   ,16000},
  { "       13"   ,12699},
  { "       10"   ,10079},
  { "        8"   ,8000},
  { "        6"   ,6350},
  { "        5"   ,5040},
  { "        4"   ,4000},
  { "      3.2"   ,3200},
  { "      3.0"   ,3175},
  { "      2.5"   ,2520},
  { "      2.0"   ,2000},
  { "      1.6"   ,1587},
  { "      1.5"   ,1587},
  { "      1.3"   ,1260},
  { "      1.0"   ,1000},
  { "      0.8"   ,800},
  { "      0.7"   ,700},
  { "      0.6"   ,600},
  { "      0.5"   ,500},
  { "      0.4"   ,400},
  { "      0.3"   ,300},
  { "      1/4"   ,250},
  { "Under 1/4"   ,200}
};

/////////////////////////////////////////////////////////////////////////////////
// Setup
/////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  Serial.print("Free memory = "); 
  Serial.println(freeMemory());
  loadNonVolatileSettings();
  initializeShutterControl();
  initializeNavchuk();
  initializeLCD();
  initializeMenu();
  initializeSteppers();
  initializeStepperTimerISR();
  initializeSplines();
  initializeLensDefogger();
  disableMotorDrivers();

  Serial.print("Free memory = "); 
  Serial.println(freeMemory());
}

/////////////////////////////////////////////////////////////////////////////////
// Main
/////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  navigationHandler();
  updateMotorPositions();
  processMotorDriverEnables();
}




