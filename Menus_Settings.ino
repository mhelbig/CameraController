/////////////////////////////////////////////////////////////////////////////////
// Load motor positions
/////////////////////////////////////////////////////////////////////////////////
void on_loadMotorPositions_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    displaySetHeading();
    lcd.setCursor(0,2);
    lcd.print("Hold Z to load");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we do the deed
    {
      loadMotorPositions();
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Save motor positions
/////////////////////////////////////////////////////////////////////////////////
void on_saveMotorPositions_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    displaySetHeading();
    lcd.setCursor(0,2);
    lcd.print("Hold Z to save");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");

    initializeSplines();
    lookupMotorPositions(0);  // move all the motors back to their starting reference positions
    updateMotorPositions();
  }

  // callback function main:
  if(motorsAreRunning()) return;  //wait until the motors get back
 
  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we do the deed
    {
      saveMotorPositions();
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Backlight Time
/////////////////////////////////////////////////////////////////////////////////
void on_backlightTime_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = backlightTimeIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(backlightTimeList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(backlightTimeList)/sizeof(backlightTimeList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(backlightTimeList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      backlightTimeIndex = tempEnumIndex;
      nunchuk.setIdleTime (backlightTimeList[backlightTimeIndex].value);
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Lens defogger PWM setting
/////////////////////////////////////////////////////////////////////////////////
void on_lensDefoggerPWM_selected(MenuItem* p_menu_item)
{
  static int tempPWMsetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempPWMsetting = lensDefoggerPWMsetting;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(lensDefoggerPWMsetting);
  }

  // callback function main:
    adjustIntValue(&lensDefoggerPWMsetting,5,100);
    lcd.setCursor(5,2);
    lcd.print(lensDefoggerPWMsetting);
    lcd.print("% ");
    initializeLensDefogger();  // also set the defogger to the new state right away

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed we keep the old value
    {
      lensDefoggerPWMsetting = tempPWMsetting;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Lens defogger mode
/////////////////////////////////////////////////////////////////////////////////
void on_lensDefoggerMode_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = lensDefoggerModeIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(lensDefoggerModeList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(lensDefoggerModeList)/sizeof(lensDefoggerModeList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(lensDefoggerModeList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      lensDefoggerModeIndex = tempEnumIndex;
      initializeLensDefogger();  // also set the defogger to the new state right away
    }
  }
}

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
    adjustIntValue(&shutterButtonTimeSetting,25,1000);
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
    adjustIntValue(&cameraRecoveryTimeSetting,25,5000);
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
    adjustIntValue(&motorSettleTimeSetting,25,5000);
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

/////////////////////////////////////////////////////////////////////////////////
// X Motor Invert
/////////////////////////////////////////////////////////////////////////////////
void on_XmotorInvert_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedXmotorInvertIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorInvertList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorInvertList)/sizeof(motorInvertList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorInvertList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedXmotorInvertIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// X Motor Enable
/////////////////////////////////////////////////////////////////////////////////
void on_XmotorEnable_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedXmotorEnableIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorEnableList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorEnableList)/sizeof(motorEnableList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorEnableList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedXmotorEnableIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// X Motor Pulses Per Rev
/////////////////////////////////////////////////////////////////////////////////
void on_XmotorPulsesPerRev_selected(MenuItem* p_menu_item)
{
  static unsigned int tempPPRsetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempPPRsetting = XmotorStepsPerRev;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(XmotorStepsPerRev);
  }

  // callback function main:
    adjustUnsignedIntValue(&XmotorStepsPerRev,50,65000);
    lcd.setCursor(5,2);
    lcd.print(XmotorStepsPerRev);
    lcd.print(" ");

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed we keep the old value
    {
      XmotorStepsPerRev = tempPPRsetting;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Y Motor Invert
/////////////////////////////////////////////////////////////////////////////////
void on_YmotorInvert_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedYmotorInvertIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorInvertList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorInvertList)/sizeof(motorInvertList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorInvertList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedYmotorInvertIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Y Motor Enable
/////////////////////////////////////////////////////////////////////////////////
void on_YmotorEnable_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedYmotorEnableIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorEnableList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorEnableList)/sizeof(motorEnableList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorEnableList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedYmotorEnableIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Z Motor Invert
/////////////////////////////////////////////////////////////////////////////////
void on_ZmotorInvert_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedZmotorInvertIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorInvertList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorInvertList)/sizeof(motorInvertList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorInvertList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedZmotorInvertIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Z Motor Enable
/////////////////////////////////////////////////////////////////////////////////
void on_ZmotorEnable_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedZmotorEnableIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorEnableList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorEnableList)/sizeof(motorEnableList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorEnableList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedZmotorEnableIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// D Motor Invert
/////////////////////////////////////////////////////////////////////////////////
void on_DmotorInvert_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedDmotorInvertIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorInvertList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorInvertList)/sizeof(motorInvertList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorInvertList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedDmotorInvertIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// D Motor Enable
/////////////////////////////////////////////////////////////////////////////////
void on_DmotorEnable_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedDmotorEnableIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorEnableList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorEnableList)/sizeof(motorEnableList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorEnableList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedDmotorEnableIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// R Motor Invert
/////////////////////////////////////////////////////////////////////////////////
void on_RmotorInvert_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedRmotorInvertIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorInvertList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorInvertList)/sizeof(motorInvertList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorInvertList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedRmotorInvertIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// R Motor Enable
/////////////////////////////////////////////////////////////////////////////////
void on_RmotorEnable_selected(MenuItem* p_menu_item)
{
  static int tempEnumIndex;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempEnumIndex = selectedRmotorEnableIndex;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(motorEnableList[tempEnumIndex].menuText);
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,(sizeof(motorEnableList)/sizeof(motorEnableList[0]))))
    {
      lcd.setCursor(5,2);
      lcd.print(motorEnableList[tempEnumIndex].menuText);
    }

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'Z')  // if Z is pressed we keep the newly adjusted value
    {
      selectedRmotorEnableIndex = tempEnumIndex;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// R Motor Pulses Per Rev
/////////////////////////////////////////////////////////////////////////////////
void on_RmotorPulsesPerRev_selected(MenuItem* p_menu_item)
{
  static unsigned int tempPPRsetting;
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    tempPPRsetting = RmotorStepsPerRev;
    lcd.clear();
    displaySetHeading();
    lcd.setCursor(5,2);
    lcd.print(RmotorStepsPerRev);
  }

  // callback function main:
    adjustUnsignedIntValue(&RmotorStepsPerRev,50,65000);
    lcd.setCursor(5,2);
    lcd.print(RmotorStepsPerRev);
    lcd.print(" ");

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'Z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'C')  // if C is pressed we keep the old value
    {
      RmotorStepsPerRev = tempPPRsetting;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Save settings to EEPROM
/////////////////////////////////////////////////////////////////////////////////
void on_saveNonVolatileSettings_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    displaySetHeading();
    lcd.setCursor(0,2);
    lcd.print("Hold Z to save");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we do the deed
    {
      saveNonVolatileSettings();
    }
  }
}
  
/////////////////////////////////////////////////////////////////////////////////
// load settings from EEPROM
/////////////////////////////////////////////////////////////////////////////////
void on_loadNonVolatileSettings_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    displaySetHeading();
    lcd.setCursor(0,2);
    lcd.print("Hold Z to load");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we do the deed
    {
      loadNonVolatileSettings();
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////
// Restore default settings
/////////////////////////////////////////////////////////////////////////////////
void on_restoreNonVolatileSettings_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    displaySetHeading();
    lcd.setCursor(0,2);
    lcd.print("Hold Z to restore");
    lcd.setCursor(0,3);
    lcd.print("Press C to cancel");
  }

  // callback function main:

  // callback function "destructor"
  if(nunchuk.userInput == 'C' || nunchuk.userInput == 'z')
  {
    ms.deselect_set_menu_item();
    displayMenu();

    if(nunchuk.userInput == 'z')  // if Z is held we do the deed
    {
      restoreDefaultSettings();
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

