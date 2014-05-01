#include <spline.h>
#include <AccelStepper.h>

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

// Setup some splines for smooth motion controls
Spline X_Spline;
Spline Y_Spline;

float X_Spline_x[7] = {-1,0,1,2,3,4, 5};
float X_Spline_y[7] = { 0,0,5,6,8,10,10};

float Y_Spline_x[7] = {-1,0,1,2,3,4, 5};
float Y_Spline_y[7] = { 0,0,2,5,8,10,10};
  
float X_Motor_Position;
float Y_Motor_Position;

// Define some steppers and the pins they will use
AccelStepper motorX(AccelStepper::DRIVER,X_STEP_PIN,X_DIR_PIN);
AccelStepper motorY(AccelStepper::DRIVER,Y_STEP_PIN,Y_DIR_PIN);

long DelayTimer;

void setup()
{
  Serial.begin(9600);
  
  X_Spline.setPoints(X_Spline_x,X_Spline_y,7);
  X_Spline.setDegree( Catmull );
 
  Y_Spline.setPoints(Y_Spline_x,Y_Spline_y,7);
  Y_Spline.setDegree( Catmull );

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  
  digitalWrite(X_ENABLE_PIN, LOW );
  digitalWrite(Y_ENABLE_PIN, LOW );

  motorX.setMaxSpeed(4000.0);
  motorX.setAcceleration(4000.0);
    
  motorY.setMaxSpeed(4000.0);
  motorY.setAcceleration(4000.0);
}

void loop()
{
  for (float i = 0; i <= 4; i+=.01)
  {
    X_Motor_Position = X_Spline.value(i) * 800;
    Y_Motor_Position = Y_Spline.value(i) * 800;
    
    Serial.print("i = "); Serial.print(i);
    Serial.print(" X_Motor = "); Serial.print(X_Motor_Position,2);
    Serial.print(" Y_Motor = "); Serial.print(Y_Motor_Position,2);
    Serial.println();
    
    motorX.moveTo(X_Motor_Position);
    motorY.moveTo(Y_Motor_Position);
    
    DelayTimer = millis()+500;

    while (DelayTimer>millis())
    {
      motorX.run();
      motorY.run();
    }
  }
  delay(1000);
}


/*
void loop()
{
    // Change direction at the limits
    if (motorX.distanceToGo() == 0)
	motorX.moveTo(-motorX.currentPosition());
    if (motorY.distanceToGo() == 0)
	motorY.moveTo(-motorY.currentPosition());

    motorX.run();
    motorY.run();
}
*/
