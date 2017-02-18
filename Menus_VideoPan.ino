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
    
    XmotorPosition = XmotorSplinePoints_y[currentTransitionSelected]; // get the current positions from the array
    YmotorPosition = YmotorSplinePoints_y[currentTransitionSelected];
    
    waitForJoystickToBeCentered = 10;   // flag that stops the joystick shift from messing up the motor positions
  }

  // callback function main:
  if(waitForJoystickToBeCentered)  // this keep the joystick being shifted as we enter the menu from messing with the motor postion
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

void on_recordVideo_selected(MenuItem* p_menu_item)
{
  static panCameraMode mode;
  static float frame;
  static float intervalTime;

  // callback function "constructor"

  if (ms.menu_item_was_just_selected())
  {
    setMotorEnableState(1);  // Turn on the motor enable lines
    updateMotorPositions();
    
    displaySetHeading();
    lcd.setCursor(0,1);
    lcd.print("Start VCR Recording");
    lcd.setCursor(0,2);
    lcd.print("Hold Z to Start pan");
    lcd.setCursor(0,3);
    lcd.print("C to cancel");
    
    mode = waitToPan;
  }

// callback function main:
  switch(mode)
  {
    case waitToPan:
//      Serial.println("waitToStart:");
      if(nunchuk.userInput == 'z')
      {
        mode = panCamera;
      }
      break;
    case panCamera:
      lookupMotorPositions(frame);
      
      updateMotorPositions();
      
      // put timing and stepping code here
      
      mode = panFinished;
      break;
    case panFinished:
      setMotorEnableState(0);  // Turn off the motor enable lines
      lcd.clear();
      lcd.setCursor(0,0);
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


