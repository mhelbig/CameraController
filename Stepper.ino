#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

// Define the steppers and the pins they will use
AccelStepper motorX(AccelStepper::DRIVER,X_STEP_PIN,X_DIR_PIN);
AccelStepper motorY(AccelStepper::DRIVER,Y_STEP_PIN,Y_DIR_PIN);

boolean stepperMotorDriverEnableState;

void initializeSteppers()
{
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  motorX.setMaxSpeed(2000.0);
  motorX.setAcceleration(3000.0);

  motorY.setMaxSpeed(2000.0);
  motorY.setAcceleration(3000.0);

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
}

void setMotorDriverEnables(boolean state)
{
  stepperMotorDriverEnableState = state;
}

void lookupMotorSplinePosition(float frame)
{
  XmotorPosition = XmotorSpline.value(frame);
  YmotorPosition = YmotorSpline.value(frame);
}

boolean motorsAreRunning(void)
{
  if (motorX.distanceToGo() != 0 || motorY.distanceToGo() != 0) return (true);
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
}
