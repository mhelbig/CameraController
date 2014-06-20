/////////////////////////////////////////////////////////////////////////////////
// Set Positions
/////////////////////////////////////////////////////////////////////////////////

void on_setPositions_selected(MenuItem* p_menu_item)
{
  static boolean waitForJoystickToBeCentered;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
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

  adjustMotorPositions(&XmotorPosition, &YmotorPosition);
  
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(0,1);
  lcd.print("X:");
  lcd.print(round(XmotorPosition));
  lcd.setCursor(10,1);
  lcd.print("Y:");
  lcd.print(round(YmotorPosition));

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
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
    localVideoTimeSetting = frameNumber[currentTransitionSelected] / videoFramesPerSecond;  // we will work with this value in time and convert it back to frames when we're done
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
      lcd.print( round(localVideoTimeSetting) * videoFramesPerSecond);
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
      frameNumber[currentTransitionSelected] = round(localVideoTimeSetting) * videoFramesPerSecond;    // make the final result a whole number
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
    ms.prev();  // move the user back to the position menu so they can set the next position
    ms.prev();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we add another spot for a transition
    {
      numberOfTransitions++;
      currentTransitionSelected=numberOfTransitions;
      XmotorSplinePoints_y[numberOfTransitions] = XmotorSplinePoints_y[numberOfTransitions-1];
      YmotorSplinePoints_y[numberOfTransitions] = YmotorSplinePoints_y[numberOfTransitions-1];
      frameNumber[numberOfTransitions] = frameNumber[numberOfTransitions-1] + 300;
      
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
// Dry Run
/////////////////////////////////////////////////////////////////////////////////
void on_dryRun_selected (MenuItem* p_menu_item)
{
  static float frame = 0;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    if (currentTransitionSelected == 1) // if only one transition setup, we can't do the dry run
    {
      ms.deselect_set_menu_item();      // so boot them right out of the menu
      displayMenu();
      return;
    }
    lcd.clear();
    displaySetHeading();
    initializeSplines();
  }
    
  if( adjustAnalogValue(&frame,0,(long)frameNumber[numberOfTransitions],false))
  {
    XmotorPosition = XmotorSpline.value(frame);
    YmotorPosition = YmotorSpline.value(frame);

    lcd.setCursor(1,1);
    lcd.print("X: ");
    lcd.print(round(XmotorPosition));
    lcd.print(" ");

    lcd.setCursor(10,1);
    lcd.print("Y: ");
    lcd.print(round(YmotorPosition));
    lcd.print(" ");

    lcd.setCursor(1,2);
    lcd.print("Video time:");
    displayAsDDHHMMSS(round(frame / videoFramesPerSecond));
    lcd.setCursor(0,3);
    lcd.print("Frame number:");
    lcd.print(round(frame));
    lcd.print("   ");

    updateMotorPositions();
  }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();
  }
}  

/////////////////////////////////////////////////////////////////////////////////
// Set Shoot Time
/////////////////////////////////////////////////////////////////////////////////
void on_set_shootTime_selected(MenuItem* p_menu_item)
{
  static float tempShootTimeSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    tempShootTimeSetting = shootTimeSetting;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  if( adjustAnalogValue(&shootTimeSetting,300,2592000,true) )   //5 minutes to 30 days
  {
    lcd.setCursor(2,1);
    displayAsDDHHMMSS(shootTimeSetting);
    lcd.setCursor(0,2);
    lcd.print("Interval:");
    displayAsDDHHMMSS( (shootTimeSetting / frameNumber[numberOfTransitions]) );
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


/////////////////////////////////////////////////////////////////////////////////
// Run Sequence
/////////////////////////////////////////////////////////////////////////////////
void on_RunSequence_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    displaySetHeading();
    lcd.setCursor(0,1);
    lcd.print("Hold Z to Start");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");

    initializeSplines();
// Move motors to start position
  }

  // callback function main:


//Modes:
// Start time setup
// Start time countdown
// for loop:
//{
//   Take shot
//   Wait shutter time
//   Move to next postion
//   Wait interval time
//}

/* these lines need some work, but will lookup the motor positions from the spline function
    X_Motor_Position = X_Spline.value(i) * 800;
    Y_Motor_Position = Y_Spline.value(i) * 800;
*/

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held, I'M NOT SURE WHAT WE DO?????
    {
    }
  }
}


