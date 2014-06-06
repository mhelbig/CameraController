/////////////////////////////////////////////////////////////////////////////////
// Timelapse menu callback functions
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
  adjustIntValue(&tempTransitionToSet,1,numberOfTransitions);  // 1 - current number of transitions
    
    lcd.setCursor(5,1);
    lcd.print(tempTransitionToSet);
    lcd.print(" of ");
    lcd.print(numberOfTransitions);

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      currentTransitionSelected = tempTransitionToSet;
    }
  }
}

void on_set_videoTime_selected(MenuItem* p_menu_item)
{
  static float tempVideoTimeSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(0,3);
    lcd.print("for transition ");
    lcd.print(currentTransitionSelected);
    
    tempVideoTimeSetting = (float)videoTimeSetting;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  if( adjustFloatValue(&tempVideoTimeSetting,5,1800,true) )  // 5 seconds to 30 minutes
    displayLongAsDDHHMMSS(round(tempVideoTimeSetting));

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      videoTimeSetting = round(tempVideoTimeSetting);
    }
  }
}

void on_setPositions_selected(MenuItem* p_menu_item)
{
  static long tempXposition;
  static long tempYposition;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
//    tempXposition = 1000;  // save a copy of the current settings in case we cancel
//    tempYposition = 1000;  
  }

  // callback function main:
//  if( adjustFloatValue(&tempVideoTimeSetting,5,1800,true) )  // 5 seconds to 30 minutes
//    displayLongAsDDHHMMSS(round(tempVideoTimeSetting));

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
//      videoTimeSetting = round(tempVideoTimeSetting);
    }
  }
}

void on_addTransition_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
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
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we add another spot for a transition
    {
      numberOfTransitions++;
      if (numberOfTransitions > MAX_NUMBER_OF_TRANSITIONS) 
      {
        numberOfTransitions = MAX_NUMBER_OF_TRANSITIONS;
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Max 5 transitions");
        delay(1500);
        displayMenu();
      }
    }
  }
}

void on_delTransition_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
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
      if (numberOfTransitions < 2)
      {
        numberOfTransitions = 2;
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Need 2 transitions");
        delay(1500);
        displayMenu();
      }
    }
  }
}

void on_set_shootTime_selected(MenuItem* p_menu_item)
{
  static float tempShootTimeSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    tempShootTimeSetting = (float)shootTimeSetting;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  if( adjustFloatValue(&tempShootTimeSetting,300,2592000,true) )  //5 minutes to 30 days
    displayLongAsDDHHMMSS(round(tempShootTimeSetting));

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      shootTimeSetting = round(tempShootTimeSetting);
    }
  }
}


void on_setStartDelay_selected(MenuItem* p_menu_item)
{
  static float tempDelayStartSetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();
    
    tempDelayStartSetting = (float)startDelayTimeSetting;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  if( adjustFloatValue(&tempDelayStartSetting,300,2592000,true) )  //5 minutes to 30 days
    displayLongAsDDHHMMSS(round(tempDelayStartSetting));

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      startDelayTimeSetting = round(tempDelayStartSetting);
    }
  }
}


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
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we add another spot for a transition
    {
    }
  }
}


