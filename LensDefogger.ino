// Define the pins used by the motors and thier drivers
#define LENS_DEFOG_OUTPUT         9

/////////////////////////////////////////////////////////////////////////////////
// Initialize Steppers
/////////////////////////////////////////////////////////////////////////////////
void initializeLensDefogger()
{
  pinMode(LENS_DEFOG_OUTPUT, OUTPUT);
  if(lensDefoggerModeList[lensDefoggerModeIndex].value == 1) // always on mode
    setLensDefoggerState(true);
  else                                                       // off or during mode
    setLensDefoggerState(false);
}

/////////////////////////////////////////////////////////////////////////////////
// Set lens defog output state
/////////////////////////////////////////////////////////////////////////////////
void setLensDefoggerState(boolean state)
{
  if(state == true)
    analogWrite(LENS_DEFOG_OUTPUT, lensDefoggerPWMsetting * 2.55);
  else
    analogWrite(LENS_DEFOG_OUTPUT, 0);
}


