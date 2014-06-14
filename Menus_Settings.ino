void on_framesPerSecond_selected(MenuItem* p_menu_item)
{
  Serial.print("fps ");
  lcd.setCursor(0,1);
  lcd.print("Frames/sec = 30");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  displayMenu();
}

void on_motionProfile_selected(MenuItem* p_menu_item)
{
  static int enumIndex = 2;
  int tempEnumIndex;
  
  enumeratedMenuList motionProfileList[]=
  {
    { "Step  " ,0},  // corresponds to the spline.cpp setDegree() function
    { "Linear" ,1},
    { "Spline" ,11}  // we use the catmull spline type because it's easer to setup
  };
  
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading();

    lcd.setCursor(5,2);
    lcd.print(motionProfileList[enumIndex].menuText);
    tempEnumIndex = enumIndex;
  }

  // callback function main:
  if(selectEnumeratedValue(&tempEnumIndex,3))
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
      enumIndex = tempEnumIndex;
      selectedMotionProfile = motionProfileList[enumIndex].value;
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

