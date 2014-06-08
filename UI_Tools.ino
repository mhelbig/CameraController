#define UI_THROTTLE_TIME 100

/////////////////////////////////////////////////////////////////////////////////
// Function to read the joystick positions as digital and adjust an integer value on the lcd display
// includes support for fine and coarse adjustment by shifting the joystick right and left
void adjustIntValue(int *value, int min, int max)
{
  static int coarseAdjust = 1;
  
  Serial.println(*value,DEC);
  
  if (nunchuk.userInput == 'R') coarseAdjust = 1;
  if (nunchuk.userInput == 'L') coarseAdjust = 10;
  if (nunchuk.userInput == 'F') *value = *value + coarseAdjust;  
  if (nunchuk.userInput == 'B') *value = *value - coarseAdjust;  
  
  Serial.println(*value);

  if(*value > max) *value = max;
  if(*value < min) *value = min;
}

/////////////////////////////////////////////////////////////////////////////////
// Function to read the analog joystick and adjust a numeric value on the lcd display
// All the math in the function is done with a float to maintain fractional precision
// result is converted back to an int or long as necessary by the calling function
boolean adjustLongValue(long *value, long min, long max, boolean adjustRateForTime, boolean initialize)
{
  static int timeAdjust = 1;
  static int coarseAdjust = 1;
  static float tempValue;
  
  if (initialize)
  {
    tempValue = float(*value);
    return(false);
  }
  
  if(adjustRateForTime);
  {
    if(*value > 60) timeAdjust = 1;
    if(*value > 3600) timeAdjust = 60;
    if(*value > 86400) timeAdjust = 1440;
  }
  
  if (nunchuk.userInput == 'R') coarseAdjust = 1;
  if (nunchuk.userInput == 'L') coarseAdjust = 10;
  
  if (uiThrottle()) return (false);  // this keeps the timing and adjust rates of UI functions consistent

  tempValue = tempValue + (
  pow( (float)nunchuk.analogDisplacementY, 3)
    * (float)nunchuk.analogDirectionY
    * timeAdjust
    * coarseAdjust
    / 20000);     // fudge factor - adjust this value to affect the overall responsiveness

  if(tempValue > max) tempValue = max;
  if(tempValue < min) tempValue = min;
  
  *value = round(tempValue);
  return (true); // this flag synchronizes display updates with the uiThrottle
}

/////////////////////////////////////////////////////////////////////////////////
// Function to select from an enumerated list and return the new value
boolean selectEnumeratedValue(int *tempValue, char listSize)
{
  delay(25);   // wait so we don't botch up wire communications between LCD and nunchuk until we find a better way to handle this
  if(nunchuk.userInput == 'B' && *tempValue < listSize-1)
  {
    (*tempValue)++;
    return (true);
  }
  if(nunchuk.userInput == 'F' && *tempValue > 0)
  {
    (*tempValue)--;
    return(true);
  }
  return(false);
}

/////////////////////////////////////////////////////////////////////////////////
void displayLongAsDDHHMMSS(long time)
{
  int day;
  int hour;
  int minute;
  int second;

  day = time/86400;
  hour = (time % 86400) / 3600;
  second=time % 3600;
  minute=second/60;
  second %= 60;

  if(time == 0)
  {
    lcd.print("           <1 s ");
    return;
  }
  if(day > 0)
  {
    if(day < 10) lcd.print(" ");
    lcd.print(day,DEC);
    lcd.print("d ");
  }
  else lcd.print("    ");
  
  if(hour > 0 || day > 0)
  {
    if(hour < 10) lcd.print("0");
    lcd.print(hour,DEC);
    lcd.print("h ");
  }
  else lcd.print("    ");
  
  if( (minute > 0 || hour > 0) && day == 0)
  {
    if(minute < 10) lcd.print("0");
    lcd.print(minute,DEC);
    lcd.print("m ");
  }
  else lcd.print("    ");
  
  if( (second > 0 || minute > 0) && hour == 0 && day == 0)
  {
    if(second < 10) lcd.print("0");
    lcd.print(second,DEC);
    lcd.print("s");
  }
  else lcd.print("    ");
}

/////////////////////////////////////////////////////////////////////////////////
// Display the menu headings and current selection
void displayMenu()
{
  Menu const* cp_menu = ms.get_current_menu();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(ms.get_current_menu()->get_name());

  lcd.setCursor(0,2);
  lcd.print(">");
  lcd.print(cp_menu->get_selected()->get_name());

//  lcd.setCursor(0,2);
//  lcd.print("Up/Dn to choose Menu");

//  lcd.setCursor(0,3);
//  lcd.print("Rt/Lf to Enter/Exit");
}

/////////////////////////////////////////////////////////////////////////////////
void displaySetHeading(void)
{
  Menu const* cp_menu = ms.get_current_menu();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(cp_menu->get_selected()->get_name());
}

/////////////////////////////////////////////////////////////////////////////////
boolean uiThrottle(void)  // this keeps the timing and adjust rates of UI functions consistent
{
  static long throttleTime;

  if(throttleTime > millis())  // we haven't yet waited long enough, tell them to bail out
    return true;
  else                         // we've waited long enough, reset the timer and tell them to process some UI
  {
    throttleTime = millis() + UI_THROTTLE_TIME;
    return (false);
  }
}

/////////////////////////////////////////////////////////////////////////////////
long round(float number)
{
  return (number >= 0) ? (long)(number + 0.5) : (long)(number - 0.5);
}  

