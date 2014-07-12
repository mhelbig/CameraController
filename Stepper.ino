// Define the pins used by the motors and thier drivers
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define D_STEP_PIN         26
#define D_DIR_PIN          28
#define D_ENABLE_PIN       24

// Setup the motor drivers
AccelStepper motorX(AccelStepper::DRIVER,X_STEP_PIN,X_DIR_PIN);
AccelStepper motorY(AccelStepper::DRIVER,Y_STEP_PIN,Y_DIR_PIN);
AccelStepper motorZ(AccelStepper::DRIVER,Z_STEP_PIN,Z_DIR_PIN);
AccelStepper motorD(AccelStepper::DRIVER,D_STEP_PIN,D_DIR_PIN);

#define MOTOR_LAGGING_THRESHOLD 10  // Motors are considered lagging if they are behind this many steps

/////////////////////////////////////////////////////////////////////////////////
// Initialize Steppers
/////////////////////////////////////////////////////////////////////////////////
void initializeSteppers()
{
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);

  pinMode(D_STEP_PIN, OUTPUT);
  pinMode(D_DIR_PIN, OUTPUT);
  pinMode(D_ENABLE_PIN, OUTPUT);

  motorX.setMaxSpeed(2000.0);
  motorX.setAcceleration(3000.0);

  motorY.setMaxSpeed(2000.0);
  motorY.setAcceleration(3000.0);

  motorZ.setMaxSpeed(2000.0);
  motorZ.setAcceleration(3000.0);

  motorD.setMaxSpeed(2000.0);
  motorD.setAcceleration(3000.0);

  Serial.println("Stepper motors initialized");
}

/////////////////////////////////////////////////////////////////////////////////
// Initialize Stepper Timer Interrupt Service Routine
/////////////////////////////////////////////////////////////////////////////////
void initializeStepperTimerISR(void)
{
  Timer3.initialize(250);         // initialize timer3 to 4KHz
  Timer3.attachInterrupt(_ISRrunSteppers);  // attach stepper motor update as a timer overflow interrupt
  Serial.println("Stepper Interrupt Service Routine Started");
}

/////////////////////////////////////////////////////////////////////////////////
// Run Motors Interrupt Service Routine
/////////////////////////////////////////////////////////////////////////////////
void _ISRrunSteppers(void)  // stepper motor ISR callback function
{
  motorX.run();
  motorY.run();
  motorZ.run();
  motorD.run();
}

/////////////////////////////////////////////////////////////////////////////////
// Enable motor drivers
/////////////////////////////////////////////////////////////////////////////////
void enableMotorDrivers(void)
{
  digitalWrite(X_ENABLE_PIN, false );
  digitalWrite(Y_ENABLE_PIN, false );
  digitalWrite(Z_ENABLE_PIN, false );
  digitalWrite(D_ENABLE_PIN, false );
}

/////////////////////////////////////////////////////////////////////////////////
// Lookup motor positions from spline array
/////////////////////////////////////////////////////////////////////////////////
void lookupMotorSplinePosition(float frame)
{
  XmotorPosition = XmotorSpline.value(frame);
  YmotorPosition = YmotorSpline.value(frame);
  ZmotorPosition = ZmotorSpline.value(frame);
  DmotorPosition = DmotorSpline.value(frame);
}

/////////////////////////////////////////////////////////////////////////////////
// Motor run status
/////////////////////////////////////////////////////////////////////////////////
boolean motorsAreRunning(void)
{
  if (motorX.distanceToGo() != 0 ||
      motorY.distanceToGo() != 0 ||
      motorZ.distanceToGo() != 0 ||
      motorD.distanceToGo() != 0   )
  return (true);
  else return (false);
}

/////////////////////////////////////////////////////////////////////////////////
// Maximum motor lag
/////////////////////////////////////////////////////////////////////////////////
int maxMotorLag(void)
{
  int xLag = abs(motorX.distanceToGo());
  int yLag = abs(motorY.distanceToGo());
  int zLag = abs(motorZ.distanceToGo());
  int dLag = abs(motorD.distanceToGo());
  int maxLag = 1;

  maxLag = max(maxLag, xLag);
  maxLag = max(maxLag, yLag);
  maxLag = max(maxLag, zLag);
  maxLag = max(maxLag, dLag);
  return(maxLag);  
}

/////////////////////////////////////////////////////////////////////////////////
// Update motor positions
/////////////////////////////////////////////////////////////////////////////////
void updateMotorPositions(void)
{
  static float PreviousXmotorPosition;
  static float PreviousYmotorPosition;
  static float PreviousZmotorPosition;
  static float PreviousDmotorPosition;
  
  if (PreviousXmotorPosition != XmotorPosition ||
      PreviousYmotorPosition != YmotorPosition ||
      PreviousZmotorPosition != ZmotorPosition ||
      PreviousDmotorPosition != DmotorPosition)
  {
    enableMotorDrivers();
  }
  
  motorX.moveTo((long)XmotorPosition * motorInvertList[selectedXmotorInvertIndex].value);
  motorY.moveTo((long)YmotorPosition * motorInvertList[selectedYmotorInvertIndex].value);
  motorZ.moveTo((long)ZmotorPosition * motorInvertList[selectedZmotorInvertIndex].value);
  motorD.moveTo((long)DmotorPosition * motorInvertList[selectedDmotorInvertIndex].value);
  
  PreviousXmotorPosition = XmotorPosition;
  PreviousYmotorPosition = YmotorPosition;
  PreviousZmotorPosition = ZmotorPosition;
  PreviousDmotorPosition = DmotorPosition;
}

/////////////////////////////////////////////////////////////////////////////////
// Process motor driver enable lines
/////////////////////////////////////////////////////////////////////////////////
void processMotorDriverEnables(void)
{
  if (motorX.distanceToGo() == 0)  // turn each motor driver off when they've finished their move
    digitalWrite(X_ENABLE_PIN, true ); 
  if(motorY.distanceToGo() == 0)
    digitalWrite(Y_ENABLE_PIN, true );
  if(motorZ.distanceToGo() == 0)
    digitalWrite(Z_ENABLE_PIN, true );
  if(motorD.distanceToGo() == 0)
    digitalWrite(D_ENABLE_PIN, true );
}

