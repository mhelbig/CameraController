/////////////////////////////////////////////////////////////////////////////////
// Constants
/////////////////////////////////////////////////////////////////////////////////
#define VIDEO_PAN_CYCLE_TIME   100  // Throttles the speed of the pan processing loop in mSec

/////////////////////////////////////////////////////////////////////////////////
// Set Pan Direction
/////////////////////////////////////////////////////////////////////////////////
void on_setPanDirection_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
// callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedPanDirectionIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(panDirectionList[tempEnumIndex].menuText);
  }

// callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(panDirectionList)/sizeof(panDirectionList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(panDirectionList[tempEnumIndex].menuText);
    }
  
// callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedPanDirectionIndex = tempEnumIndex;
    }
  }  
}

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
// Set Pan Overshoot Time
/////////////////////////////////////////////////////////////////////////////////
void on_set_Pan_Overshoot_selected(MenuItem* p_menu_item)
{
  static int tempPanOvershootSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(7,2);
    lcd.print("s");
    
    tempPanOvershootSetting = panOvershootTime;  // save a copy of the current setting in case we cancel
  }
  // callback function main:
  adjustIntValue(&panOvershootTime,0,5);
  lcd.setCursor(6,2);
  lcd.print(panOvershootTime);

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed, restore the orignal value
    {
      panOvershootTime = tempPanOvershootSetting;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Set Pan Revolutions
/////////////////////////////////////////////////////////////////////////////////
void on_set_PanRevs_selected(MenuItem* p_menu_item)
{
  static int tempPanRevsSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    tempPanRevsSetting = panRevsSetting;  // save a copy of the current setting in case we cancel
  }
  
  // callback function main:
  adjustIntValue(&panRevsSetting,10,400);
  lcd.setCursor(2,2);
  lcd.print((float)panRevsSetting/100);
  lcd.print(" ");
  
  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed, restore the orignal value
    {
      panRevsSetting = tempPanRevsSetting;
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
    
    XmotorPosition = XmotorPanHomePosition;   // start out at the last home position 
    YmotorPosition = YmotorPanHomePosition;
    
    waitForJoystickToBeCentered = 10;   // flag that stops the joystick shift from messing up the motor positions
  }

  // callback function main:
  if(waitForJoystickToBeCentered)  // this keep the joystick being shifted as we enter the menu from messing with the motor position
  {
    if(nunchuk.analogDisplacementX == 0) waitForJoystickToBeCentered--;
    return;
  }

  setMotorEnableState(1);  // Turn on the motor enable lines
  if(adjustMotorPositions(&XmotorPosition, &YmotorPosition, -1000000, 1000000, -1000000, 1000000))  // no real limits on positions for pan and tilt
  {
    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("X:");
    lcd.print(round(XmotorPosition));
    lcd.setCursor(10,1);
    lcd.print("Y:");
    lcd.print(round(YmotorPosition));
  }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    setMotorEnableState(0);  // Turn off the motor enable lines

    XmotorPanHomePosition = XmotorPosition;   // save the home positions
    YmotorPanHomePosition = YmotorPosition;

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

    panStepsPerSecond = ( ( (float)panRevsSetting/100) * XmotorStepsPerRev) / panTimeSetting;
    panTime = 0 - panOvershootTime;  //set the starting point
    XmotorPosition = XmotorPanHomePosition + ( panStepsPerSecond * panTime * panDirectionList[selectedPanDirectionIndex].value );  // move the motors to the home position
    YmotorPosition = YmotorPanHomePosition;
    
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
        generalPurposeTimer.init(VIDEO_PAN_CYCLE_TIME);
        
        lcd.clear();
        displaySetHeading();
        lcd.setCursor(0,1);
        lcd.print("    Time: ");
        lcd.setCursor(0,2);
        lcd.print("Position: ");
        
        mode = panCamera;
      }
      break;
    case panCamera:
      if (generalPurposeTimer.expired())
      {
        generalPurposeTimer.addTime(VIDEO_PAN_CYCLE_TIME);

       if(panTime > (panTimeSetting + panOvershootTime))
       {
          mode = panFinished;
       }

        XmotorPosition = XmotorPanHomePosition + (panStepsPerSecond * panTime * panDirectionList[selectedPanDirectionIndex].value);  // calculate the pan motor position
        
        lcd.setCursor(10,1);
        lcd.print(panTime,0); lcd.print(" ");
        lcd.setCursor(10,2);
        lcd.print(XmotorPosition,0);  lcd.print(" ");
        panTime += ((float)VIDEO_PAN_CYCLE_TIME/1000);                                // increment the pan time
      }
      break;
    case panFinished:
      setMotorEnableState(0);  // Turn off the motor enable lines
      lcd.setCursor(0,3);
      lcd.print("Completed. Press 'C'");
      break;
  }

// callback function "destructor"
  if(nunchuk.userInput == 'C')
  {
    ms.deselect_set_menu_item();
    displayMenu();
  }
}


