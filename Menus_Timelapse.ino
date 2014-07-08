/////////////////////////////////////////////////////////////////////////////////
// Set Camera Exposure Time
/////////////////////////////////////////////////////////////////////////////////
void on_setExposureTime_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
// callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedExposureIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(15,2);
    lcd.print("Sec");
    lcd.setCursor(3,2);
    lcd.print(cameraExposureTime[tempEnumIndex].menuText);
  }

// callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(cameraExposureTime)/sizeof(cameraExposureTime[0]))))
    {
      lcd.setCursor(3,2);
      lcd.print(cameraExposureTime[tempEnumIndex].menuText);
    }
  
// callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedExposureIndex = tempEnumIndex;
    }
  }  
}

/////////////////////////////////////////////////////////////////////////////////
// Select transition
/////////////////////////////////////////////////////////////////////////////////
void on_transitionToSet_selected(MenuItem* p_menu_item)
{
  static int tempTransitionToSet;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    if (numberOfTransitions == 1) // if only one transition setup, we can't do the dry run
    {
      ms.deselect_set_menu_item();      // so boot them right out of the menu
      displayMenu();
      return;
    }
    lcd.clear();
    displaySetHeading();
    
    tempTransitionToSet = currentTransitionSelected;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  adjustIntValue(&currentTransitionSelected,1,numberOfTransitions);  // 1 - current number of transitions
  lcd.setCursor(5,1);
  lcd.print(currentTransitionSelected);
  lcd.print(" of ");
  lcd.print(numberOfTransitions);

// callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if c is pressed, restore the original value
    {
      currentTransitionSelected = tempTransitionToSet;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Set Video Time
/////////////////////////////////////////////////////////////////////////////////

void on_set_videoTime_selected(MenuItem* p_menu_item)
{
  static float tempVideoTimeSetting;
  static float localVideoTimeSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    if (currentTransitionSelected == 1) // the first transition must be left at zero time
    {
      ms.deselect_set_menu_item();      // so boot them right out of the menu
      displayMenu();
      return;
    }

    lcd.clear();
    displaySetHeading();
    lcd.setCursor(0,3);
    lcd.print("@ transition ");
    lcd.print(currentTransitionSelected);
    
    tempVideoTimeSetting = frameNumber[currentTransitionSelected];  // save a copy of the current setting in case we cancel
    localVideoTimeSetting = frameNumber[currentTransitionSelected] / framesPerSecondList[videoFramesPerSecondIndex].value;  // we will work with this value in time and convert it back to frames when we're done
  }

  // callback function main:
  if( adjustAnalogValue(&localVideoTimeSetting,5,1800,true) )  // 5 seconds to 30 minutes
  {
    lcd.setCursor(2,1);
    displayAsDDHHMMSS(localVideoTimeSetting);
    if (currentTransitionSelected == numberOfTransitions)
    {
      lcd.setCursor(0,2);
      lcd.print("frames req'd: ");
      lcd.print( round(localVideoTimeSetting) * framesPerSecondList[videoFramesPerSecondIndex].value);
      lcd.print(" ");
    }

  }
  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed, restore the original value
    {
      frameNumber[currentTransitionSelected] = tempVideoTimeSetting;
    }
    else
    {
      frameNumber[currentTransitionSelected] = 
      round(localVideoTimeSetting) 
      * framesPerSecondList[videoFramesPerSecondIndex].value;    // make the final result a whole number
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Set Pan and Tilt positions
/////////////////////////////////////////////////////////////////////////////////

void on_setPanTilt_selected(MenuItem* p_menu_item)
{
  static boolean waitForJoystickToBeCentered;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    setMotorDriverEnables(true);
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(0,3);
    lcd.print("@ transition ");
    lcd.print(currentTransitionSelected);
    
    XmotorPosition = XmotorSplinePoints_y[currentTransitionSelected]; // get the current position from the array
    YmotorPosition = YmotorSplinePoints_y[currentTransitionSelected];
    
    waitForJoystickToBeCentered = 1;   // flag that stops the joystick shift from messing up the motor positions
  }

  // callback function main:
  if(waitForJoystickToBeCentered)  // this keep the joystick being shifted as we enter the menu from messing with the motor postion
  {
    if(nunchuk.analogDisplacementX == 0) waitForJoystickToBeCentered = 0;
    return;
  }

  if(adjustMotorPositions(&XmotorPosition, &YmotorPosition))
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
    setMotorDriverEnables(false);
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed save the new values back into the motor array
    {
      XmotorSplinePoints_y[currentTransitionSelected] = round(XmotorPosition);
      YmotorSplinePoints_y[currentTransitionSelected] = round(YmotorPosition);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Set Zoom and Dolly positions
/////////////////////////////////////////////////////////////////////////////////

void on_setZoomDolly_selected(MenuItem* p_menu_item)
{
  static boolean waitForJoystickToBeCentered;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    setMotorDriverEnables(true);
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(0,3);
    lcd.print("@ transition ");
    lcd.print(currentTransitionSelected);
    
    ZmotorPosition = ZmotorSplinePoints_y[currentTransitionSelected]; // get the current position from the array
    DmotorPosition = DmotorSplinePoints_y[currentTransitionSelected];
    
    waitForJoystickToBeCentered = 1;   // flag that stops the joystick shift from messing up the motor positions
  }

  // callback function main:
  if(waitForJoystickToBeCentered)  // this keep the joystick being shifted as we enter the menu from messing with the motor postion
  {
    if(nunchuk.analogDisplacementX == 0) waitForJoystickToBeCentered = 0;
    return;
  }

  if(adjustMotorPositions(&DmotorPosition, &ZmotorPosition))
  {
    lcd.setCursor(0,1);
    lcd.print("                    ");
    lcd.setCursor(0,1);
    lcd.print("D:");
    lcd.print(round(DmotorPosition));
    lcd.setCursor(10,1);
    lcd.print("Z:");
    lcd.print(round(ZmotorPosition));
  }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    setMotorDriverEnables(false);
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed save the new values back into the motor array
    {
      ZmotorSplinePoints_y[currentTransitionSelected] = round(ZmotorPosition);
      DmotorSplinePoints_y[currentTransitionSelected] = round(DmotorPosition);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Add Transition
/////////////////////////////////////////////////////////////////////////////////
void on_addTransition_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    if(numberOfTransitions >= MAX_NUMBER_OF_TRANSITIONS) // jump out of the menu if we're at the max
    {
      ms.deselect_set_menu_item();
      displayMenu();
      return;
    }      
    displaySetHeading();
    lcd.print(" #");
    lcd.print(numberOfTransitions+1);
    lcd.setCursor(0,1);
    lcd.print("Hold Z to add");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    ms.prev();  // move the user back to the pan/tilt menu so they can set the next position
    ms.prev();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we add another spot for a transition
    {
      numberOfTransitions++;
      currentTransitionSelected=numberOfTransitions;
      XmotorSplinePoints_y[numberOfTransitions] = XmotorSplinePoints_y[numberOfTransitions-1];
      YmotorSplinePoints_y[numberOfTransitions] = YmotorSplinePoints_y[numberOfTransitions-1];
      ZmotorSplinePoints_y[numberOfTransitions] = ZmotorSplinePoints_y[numberOfTransitions-1];
      DmotorSplinePoints_y[numberOfTransitions] = DmotorSplinePoints_y[numberOfTransitions-1];
      frameNumber[numberOfTransitions] = frameNumber[numberOfTransitions-1] + 300;
      
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Delete last transition
/////////////////////////////////////////////////////////////////////////////////
void on_delTransition_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    if(numberOfTransitions <= 1) // jump out of the menu if we're at the min number of transitions
    {
      ms.deselect_set_menu_item();
      displayMenu();
      return;
    }      
    displaySetHeading();
    lcd.print(" #");
    lcd.print(numberOfTransitions);
    lcd.setCursor(0,1);
    lcd.print("Hold Z to delete");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we add another spot for a transition
    {
      numberOfTransitions--;
      if (currentTransitionSelected > numberOfTransitions) currentTransitionSelected = numberOfTransitions;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Set Shoot Time
/////////////////////////////////////////////////////////////////////////////////
void on_set_shootTime_selected(MenuItem* p_menu_item)
{
  static float tempShootTimeSetting;
  static float minimumShootTime;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    if (numberOfTransitions == 1) // if only one transition setup, we can't do the dry run
    {
      ms.deselect_set_menu_item();      // so boot them right out of the menu
      displayMenu();
      return;
    }
    lcd.clear();
    displaySetHeading();
    
    tempShootTimeSetting = shootTimeSetting;  // save a copy of the current setting in case we cancel
    minimumShootTime = (cameraExposureTime[selectedExposureIndex].value
                        + postShootTimeDelaySetting
                        + cameraRecoveryTimeSetting 
                        + motorSettleTimeSetting)
                        *frameNumber[numberOfTransitions]/1000;
  }

  // callback function main:
  if( adjustAnalogValue(&shootTimeSetting,minimumShootTime,2592000,true) )   //calcuated min based on exposure time up to 30 days
  {
    lcd.setCursor(2,1);
    displayAsDDHHMMSS(shootTimeSetting);
    lcd.setCursor(0,2);
    lcd.print("Interval:");
    lcd.print( (shootTimeSetting / frameNumber[numberOfTransitions]) );  //displayAsDDHHMMSS
    lcd.print(" sec  ");
  }
  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed, restore the orignal value
    {
      shootTimeSetting = tempShootTimeSetting;
    }
    else
    {
      shootTimeSetting = round(shootTimeSetting);    // make the final result a whole number
    }
  }
}


/////////////////////////////////////////////////////////////////////////////////
// Dry Run
/////////////////////////////////////////////////////////////////////////////////
void on_dryRun_selected (MenuItem* p_menu_item)
{
  static float frame;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    if (numberOfTransitions == 1) // if only one transition setup, we can't do the dry run
    {
      ms.deselect_set_menu_item();      // so boot them right out of the menu
      displayMenu();
      return;
    }
    setMotorDriverEnables(true);
    lcd.clear();
    displaySetHeading();
    initializeSplines();
    frame = 0;
  }
    
  if( adjustAnalogValue(&frame,0,(long)frameNumber[numberOfTransitions],false))
  {
    lookupMotorSplinePosition(frame);
    updateMotorPositions();
    
    displayMotorPositions();
//    displayVideoTime(frame);
    displayFrameNumber(frame,frameNumber[numberOfTransitions]);
  }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    setMotorDriverEnables(false);
    ms.deselect_set_menu_item();
    displayMenu();
  }
}  

/////////////////////////////////////////////////////////////////////////////////
// Set Start Delay
/////////////////////////////////////////////////////////////////////////////////
void on_setStartDelay_selected(MenuItem* p_menu_item)
{
  static float tempStartDelayTimeSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    tempStartDelayTimeSetting = startDelayTimeSetting;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  if( adjustAnalogValue(&startDelayTimeSetting,0,2592000,true) )  //5 minutes to 30 days
  {
    lcd.setCursor(2,1);
    displayAsDDHHMMSS(startDelayTimeSetting);
  }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed, restore the original value
    {
      startDelayTimeSetting = tempStartDelayTimeSetting;
    }
    else
    {
      startDelayTimeSetting = round(startDelayTimeSetting);    // make the final result a whole number
  }
  }
}

NBtimer intervalTimer;
NBtimer exposureTimer;
NBtimer motorSettleTimer;
NBtimer generalPurposeTimer;

/////////////////////////////////////////////////////////////////////////////////
// Run Sequence
/////////////////////////////////////////////////////////////////////////////////
enum shootSequenceMode
{
  waitForMotors,
  waitToStart,
  waitStartDelay,
  shootFrame,
  waitExposureTime,
  waitMotorSettleTime,
  incrementFrame,
  moveMotorsToPosition,
  waitIntervalTime,
  sequenceFinished
};

void on_RunSequence_selected(MenuItem* p_menu_item)
{
  static shootSequenceMode mode;
  static float frame;
  static float intervalTime;

  // callback function "constructor"

  if (ms.menu_item_was_just_selected())
  {
    if (numberOfTransitions == 1) // if only one transition setup, we can't do the dry run
    {
      ms.deselect_set_menu_item();      // so boot them right out of the menu
      displayMenu();
      return;
    }
    frame = 0;
    intervalTime = (shootTimeSetting / frameNumber[numberOfTransitions] * 1000);
    setMotorDriverEnables(true);
    initializeSplines();
    lookupMotorSplinePosition(frame);
    updateMotorPositions();

    displaySetHeading();
    lcd.setCursor(0,1);
    lcd.print("Hold Z to Start");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");
    
    mode = waitForMotors;
  }

// callback function main:
  switch(mode)
  {
    case waitForMotors:
//      Serial.println("waitForMotors:");
      if(motorsAreRunning()) return;  //wait until the motors reach the home position
      else mode = waitToStart;
      break;
    case waitToStart:
//      Serial.println("waitToStart:");
      if(nunchuk.userInput == 'z')
      {
        lcd.setCursor(0,1);
        lcd.print("Starting in:       ");
        generalPurposeTimer.init(startDelayTimeSetting+500);  // Add a half second to allow for the focus button to process
        mode = waitStartDelay;
      }
      break;
    case waitStartDelay:
//      Serial.println("waitStartDelay:");
      lcd.setCursor(0,2);
      displayAsDDHHMMSS(generalPurposeTimer.remaining() / 1000);
      if (generalPurposeTimer.expired())
      {
        lcd.setCursor(0,1);
        lcd.print("                    ");
        lcd.setCursor(0,2);
        lcd.print("                    ");
        lcd.setCursor(0,3);
        lcd.print("                    ");
        intervalTimer.init(intervalTime);    // start the interval time
        generalPurposeTimer.init(shutterButtonTimeSetting + postShootTimeDelaySetting);

        if(generalPurposeTimer.remaining() < 250);
        {
          pressFocusButton();
        }
        mode = shootFrame;
      }
      break;  
    case shootFrame:
        pressShutterButton();
      if (generalPurposeTimer.expired())
      {
//        Serial.println("releasing shutter button");
        releaseShutterButton();
        exposureTimer.init(cameraExposureTime[selectedExposureIndex].value);
        motorSettleTimer.init(motorSettleTimeSetting);

        lcd.setCursor(19,3);
        lcd.print("E");
        mode = waitExposureTime;
      }
      break;
    case waitExposureTime:
//      Serial.println("waitExposureTime");
      if(exposureTimer.expired())
      {

        lcd.setCursor(19,3);
        lcd.print("M");
        mode = waitMotorSettleTime;
      }
      else
      {
        lcd.setCursor(15,3);
        lcd.print(((intervalTimer.remaining())/1000)+1);
        lcd.print("s ");
        Serial.print(".");
      }        
      break;
    case waitMotorSettleTime:
//      Serial.println("waitMotorSettleTime");
      if(motorSettleTimer.expired())
      {
        lcd.setCursor(19,3);
        lcd.print("I");
        mode = incrementFrame;
      }
      else
      {
        lcd.setCursor(15,3);
        lcd.print(((intervalTimer.remaining())/1000)+1);
        lcd.print("s ");
        Serial.print(".");
      }        
      break;
    case incrementFrame:
      frame ++;
      if(frame > frameNumber[numberOfTransitions]) mode = sequenceFinished;
      else mode = moveMotorsToPosition;
      break;
    case moveMotorsToPosition:
      setMotorDriverEnables(true);
      lookupMotorSplinePosition(frame);
      updateMotorPositions();
      setMotorDriverEnables(false);
      mode = waitIntervalTime;
      displayMotorPositions();
      displayFrameNumber(frame,frameNumber[numberOfTransitions]);
      break;
    case waitIntervalTime:
//      Serial.println("waitIntervalTime:");
      if (intervalTimer.expired())
      {
        intervalTimer.addTime(intervalTime);
        mode = shootFrame;
        
//        Serial.println(".");
      }
      else
      {
        lcd.setCursor(15,3);
        lcd.print((intervalTimer.remaining()/1000)+1);
        lcd.print("s ");
      }        
      break;
    case sequenceFinished:
//      Serial.println("sequence finished");
      releaseFocusButton();
      setMotorDriverEnables(false);
      break;
  }
 

// callback function "destructor"
  if(nunchuk.userInput == 'C')
  {
    setMotorDriverEnables(false);
    releaseFocusButton();
    ms.deselect_set_menu_item();
    displayMenu();
  }
}


