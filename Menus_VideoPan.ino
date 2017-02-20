/////////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////////
#define VIDEO_PAN_CYCLE_TIME   20  // Throttles the speed of the pan processing loop in mSec

/////////////////////////////////////////////////////////////////////////////////
// Set Pan Time
/////////////////////////////////////////////////////////////////////////////////
void on_set_PanTime_selected(MenuItem* p_menu_item)
{
  static float tempPanTimeSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    tempPanTimeSetting = panTimeSetting;  // save a copy of the current setting in case we cancel
  }
  // callback function main:
  if(adjustAnalogValue(&panTimeSetting,10,3600,true))   //calcuated min based on exposure time up to 1 hour
  {
    lcd.setCursor(2,2);
    displayAsDDHHMMSS(panTimeSetting);
  }
  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed, restore the orignal value
    {
      panTimeSetting = tempPanTimeSetting;
    }
    else
    {
      panTimeSetting = round(panTimeSetting);    // make the final result a whole number
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Set Pan Revolutions
/////////////////////////////////////////////////////////////////////////////////
void on_set_PanRevs_selected(MenuItem* p_menu_item)
{
  static float tempPanRevsSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    tempPanRevsSetting = panRevsSetting;  // save a copy of the current setting in case we cancel
  }
  // callback function main:
  if(adjustAnalogValue(&panRevsSetting,.01,25,false))
  {
    lcd.setCursor(2,2);
    lcd.print((round(panRevsSetting*100 +0.5)) / 100);
    lcd.print(" ");
  }
  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed, restore the orignal value
    {
      panRevsSetting = tempPanRevsSetting;
    }
    else
    {
      panRevsSetting = panRevsSetting;    // round the result to 2 decimal places
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Set initial Pan and Tilt positions
/////////////////////////////////////////////////////////////////////////////////

void on_initialPanTilt_selected(MenuItem* p_menu_item)
{
  static boolean waitForJoystickToBeCentered;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    waitForJoystickToBeCentered = 10;   // flag that stops the joystick shift from messing up the motor positions
  }

  // callback function main:
  if(waitForJoystickToBeCentered)  // this keep the joystick being shifted as we enter the menu from messing with the motor position
  {
    if(nunchuk.analogDisplacementX == 0) waitForJoystickToBeCentered--;
    return;
  }

  setMotorEnableState(1);  // Turn on the motor enable lines
  if(adjustMotorPositions(&XmotorPanHomePosition, &YmotorPanHomePosition, -1000000, 1000000, -1000000, 1000000))  // no real limits on positions for pan and tilt
  {
    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("X:");
    lcd.print(round(XmotorPanHomePosition));
    lcd.setCursor(10,1);
    lcd.print("Y:");
    lcd.print(round(YmotorPanHomePosition));
  }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    setMotorEnableState(0);  // Turn off the motor enable lines
    ms.deselect_set_menu_item();
    displayMenu();
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Pan Camera
/////////////////////////////////////////////////////////////////////////////////
enum panCameraMode
{
  waitToPan,
  panCamera,
  panFinished
};

static float panStepsPerSecond;

void on_recordVideo_selected(MenuItem* p_menu_item)
{
  static panCameraMode mode;

  // callback function "constructor"

  if (ms.menu_item_was_just_selected())
  {
    setMotorEnableState(1);  // Turn on the motor enable lines
    updateMotorPositions();
    
    displaySetHeading();
    lcd.setCursor(0,1);
    lcd.print("Start VCR Record");
    lcd.setCursor(0,2);
    lcd.print("Press Z to Start pan");
    lcd.setCursor(0,3);
    lcd.print("C to cancel");
    
    mode = waitToPan;
  }

// callback function main:
  switch(mode)
  {
    case waitToPan:
//      Serial.println("waitToStart:");
      if(nunchuk.userInput == 'Z')
      {
        panStepsPerSecond = (panRevsSetting * XmotorStepsPerRev) / panTimeSetting;
        generalPurposeTimer.init(VIDEO_PAN_CYCLE_TIME);
        panTime = 0 - panOvershootTime;  //set the starting point
        
        lcd.clear();
        displaySetHeading();
        
        mode = panCamera;
      }
      break;
    case panCamera:
      if (generalPurposeTimer.expired())
      {
        generalPurposeTimer.addTime(VIDEO_PAN_CYCLE_TIME);
        updateMotorPanPosition;
        
        XmotorPanPosition = XmotorPanHomePosition + (panStepsPerSecond * panTime);  // calculate the pan motor position
        
        // FIX THE ROUNDING OF THIS CALCULATION TO ZERO:   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        panTime += (float)(VIDEO_PAN_CYCLE_TIME/1000);                                // increment the pan time
        
        lcd.setCursor(0,1);
        lcd.print(panTime,1);
        lcd.setCursor(0,2);
        lcd.print(XmotorPanPosition,0);
      }

     if(panTime > (panTimeSetting + panOvershootTime))
     {
       mode = panFinished;
       setMotorEnableState(0);  // Turn off the motor enable lines
      lcd.setCursor(0,3);
      lcd.print("Completed. Press 'C'");
     }
      break;
    case panFinished:

      break;
  }

// callback function "destructor"
  if(nunchuk.userInput == 'C')
  {
    ms.deselect_set_menu_item();
    displayMenu();
  }
}


