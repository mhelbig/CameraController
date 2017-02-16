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



