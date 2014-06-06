#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

// Define the steppers and the pins they will use
AccelStepper motorX(AccelStepper::DRIVER,X_STEP_PIN,X_DIR_PIN);
AccelStepper motorY(AccelStepper::DRIVER,Y_STEP_PIN,Y_DIR_PIN);

void initializeSteppers()
{
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);

  digitalWrite(X_ENABLE_PIN, LOW );
  digitalWrite(Y_ENABLE_PIN, LOW );

  motorX.setMaxSpeed(1000.0);
  motorX.setAcceleration(1000.0);

  motorY.setMaxSpeed(300.0);
  motorY.setAcceleration(1000.0);

  Serial.println("Stepper motors initialized");
}

void runSteppers(void)
{
  motorX.run();
  motorY.run();
}

void exampleCode(void)
{
    motorX.moveTo(1000);
  motorY.moveTo(1000);

  // Change direction at the limits
  if (motorX.distanceToGo() == 0)
    motorX.moveTo(-motorX.currentPosition());
  if (motorY.distanceToGo() == 0)
    motorY.moveTo(-motorY.currentPosition());
}
