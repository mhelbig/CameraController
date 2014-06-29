/////////////////////////////////////////////////////////////////////////////////
// Frames Per Second
/////////////////////////////////////////////////////////////////////////////////
void on_framesPerSecond_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = videoFramesPerSecondIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(framesPerSecondList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(framesPerSecondList)/sizeof(framesPerSecondList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(framesPerSecondList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      videoFramesPerSecondIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Shutter Button Time
/////////////////////////////////////////////////////////////////////////////////
void on_shutterButtonTime_selected(MenuItem* p_menu_item)
{
  static long tempShutterButtonTimeSetting;
 
// callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempShutterButtonTimeSetting = shutterButtonTimeSetting;
    displaySetHeading();
    lcd.setCursor(5,2);
  }  
  
// callback function main:
    adjustIntValue(&shutterButtonTimeSetting,25,500);
    lcd.setCursor(5,2);
    lcd.print(shutterButtonTimeSetting);
    lcd.print("mS ");
// callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if c is pressed, restore the original value
    {
      shutterButtonTimeSetting = tempShutterButtonTimeSetting;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Camera Recovery Time
/////////////////////////////////////////////////////////////////////////////////
void on_cameraRecoveryTime_selected(MenuItem* p_menu_item)
{
  static long tempCameraRecoveryTimeSetting;
 
// callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempCameraRecoveryTimeSetting = cameraRecoveryTimeSetting;
    displaySetHeading();
    lcd.setCursor(5,2);
  }  
  
// callback function main:
    adjustIntValue(&cameraRecoveryTimeSetting,25,500);
    lcd.setCursor(5,2);
    lcd.print(cameraRecoveryTimeSetting);
    lcd.print("mS ");
// callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if c is pressed, restore the original value
    {
      cameraRecoveryTimeSetting = tempCameraRecoveryTimeSetting;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Motor Settle Time
/////////////////////////////////////////////////////////////////////////////////
void on_motorSettleTime_Selected(MenuItem* p_menu_item)
{
  static long tempMotorSettleTimeSetting;
 
// callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempMotorSettleTimeSetting = motorSettleTimeSetting;
    displaySetHeading();
    lcd.setCursor(5,2);
  }  
  
// callback function main:
    adjustIntValue(&motorSettleTimeSetting,25,500);
    lcd.setCursor(5,2);
    lcd.print(motorSettleTimeSetting);
    lcd.print("mS ");
// callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if c is pressed, restore the original value
    {
      motorSettleTimeSetting = tempMotorSettleTimeSetting;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Motion Profile
/////////////////////////////////////////////////////////////////////////////////
void on_motionProfile_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedMotionProfileIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motionProfileList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motionProfileList)/sizeof(motionProfileList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motionProfileList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedMotionProfileIndex = tempEnumIndex;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// FREE MEMORY Display
///////////////////////////////////////////////////////////////////////////////////////////////////
void on_FreeMem_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Free Memory =");
    lcd.setCursor(14,1);
    lcd.print(freeMemory(),DEC); 
    lcd.setCursor(0,3);
    lcd.print("Press Z to Exit"); 
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();
  }
}

