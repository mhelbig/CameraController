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

// Define the steppers and the pins they will use
AccelStepper motorX(AccelStepper::DRIVER,X_STEP_PIN,X_DIR_PIN);
AccelStepper motorY(AccelStepper::DRIVER,Y_STEP_PIN,Y_DIR_PIN);
AccelStepper motorZ(AccelStepper::DRIVER,Z_STEP_PIN,Z_DIR_PIN);
AccelStepper motorD(AccelStepper::DRIVER,D_STEP_PIN,D_DIR_PIN);

boolean stepperMotorDriverEnableState;

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

void initializeStepperTimerISR(void)
{
  Timer3.initialize(250);         // initialize timer3 to 4KHz
  Timer3.attachInterrupt(_ISRrunSteppers);  // attach stepper motor update as a timer overflow interrupt
  Serial.println("Stepper Interrupt Service Routine Started");
}

void _ISRrunSteppers(void)  // stepper motor ISR callback function
{
  motorX.run();
  motorY.run();
  motorZ.run();
  motorD.run();
}

void setMotorDriverEnables(boolean state)
{
  stepperMotorDriverEnableState = state;
}

void lookupMotorSplinePosition(float frame)
{
  XmotorPosition = XmotorSpline.value(frame);
  YmotorPosition = YmotorSpline.value(frame);
  ZmotorPosition = ZmotorSpline.value(frame);
  DmotorPosition = DmotorSpline.value(frame);
}

boolean motorsAreRunning(void)
{
  if (motorX.distanceToGo() != 0 ||
      motorY.distanceToGo() != 0 ||
      motorZ.distanceToGo() != 0 ||
      motorD.distanceToGo() != 0)
  return (true);
  else return (false);
}

void updateMotorPositions(void)
{
  motorX.moveTo((long)XmotorPosition);
  if (stepperMotorDriverEnableState == true)
  {
    digitalWrite(X_ENABLE_PIN, false );  // turn the motor drivers on anytime they're enabled
  }
  else if (motorX.distanceToGo() == 0)
  {
    digitalWrite(X_ENABLE_PIN, true ); // only turn them off when they've finished their move
  }
 
  motorY.moveTo((long)YmotorPosition);
  if (stepperMotorDriverEnableState == true)
  {
    digitalWrite(Y_ENABLE_PIN, false );  // turn the motor drivers on anytime they're enabled
  }
  else if(motorY.distanceToGo() == 0)
  {
    digitalWrite(Y_ENABLE_PIN, true ); // only turn them off when they've finished their move
  }

  motorZ.moveTo((long)ZmotorPosition);
  if (stepperMotorDriverEnableState == true)
  {
    digitalWrite(Z_ENABLE_PIN, false );  // turn the motor drivers on anytime they're enabled
  }
  else if(motorZ.distanceToGo() == 0)
  {
    digitalWrite(Z_ENABLE_PIN, true ); // only turn them off when they've finished their move
  }

  motorD.moveTo((long)DmotorPosition);
  if (stepperMotorDriverEnableState == true)
  {
    digitalWrite(D_ENABLE_PIN, false );  // turn the motor drivers on anytime they're enabled
  }
  else if(motorD.distanceToGo() == 0)
  {
    digitalWrite(D_ENABLE_PIN, true ); // only turn them off when they've finished their move
  }
}
