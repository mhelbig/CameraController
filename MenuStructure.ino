//When adding menu components, add them to each of the three sections:
//
//  Menu structure:   Defines the names for each menu item which is displayed on the LCD
//  initialize:       Adds each item to the menu structure
//  Callback:         Associates each selectable menu item to a function

/////////////////////////////////////////////////////////////////////////////////
// Global variables
/////////////////////////////////////////////////////////////////////////////////
long shootTimeSetting = 3600;
float tempShootTimeSetting;
long videoTimeSetting = 30;
float tempVideoTimeSetting;


/////////////////////////////////////////////////////////////////////////////////
// Menu structure
/////////////////////////////////////////////////////////////////////////////////
//Root menu
MenuSystem ms;
Menu mm("Camera Controller");
//Timelapse menu
Menu tlMenu("Run Timelapse");
MenuItem videoTime("Set video time");
MenuItem shootTime("Set shoot time");
//panoramic menu
Menu pmMenu("Run 360 Panograph");
MenuItem pm_autoMode("Panograph Auto");
//Setup menu
Menu suMenu("Change Settings");
MenuItem framesPerSecond("Frames/sec");
MenuItem motionProfile("Motion Profile");
MenuItem Xmotion("X (Pan) Motion");
MenuItem Ymotion("Y (Tilt) Motion");
MenuItem Zmotion("Z (Zoom) Motion");
MenuItem Dmotion("D (Dolly) Motion");
MenuItem Rmotion("R (Rotate) Motion");
MenuItem FreeMem("Free Memory");

/////////////////////////////////////////////////////////////////////////////////
// Initialize
/////////////////////////////////////////////////////////////////////////////////
void initializeMenu(void)
{
  //Timelapse menu
  mm.add_menu(&tlMenu);
  tlMenu.add_item(&videoTime, &on_videoTime_selected);
  tlMenu.add_item(&shootTime, &on_shootTime_selected);
  //Panoramic menu
  mm.add_menu(&pmMenu);
  pmMenu.add_item(&pm_autoMode, &on_pm_autoMode_selected);
  //Setup menu
  mm.add_menu(&suMenu);
  suMenu.add_item(&framesPerSecond, &on_framesPerSecond_selected);
  suMenu.add_item(&motionProfile, &on_motionProfile_selected);
  suMenu.add_item(&Xmotion, &on_Xmotion_selected);
  suMenu.add_item(&Ymotion, &on_Ymotion_selected);
  suMenu.add_item(&Zmotion, &on_Zmotion_selected);
  suMenu.add_item(&Dmotion, &on_Dmotion_selected);
  suMenu.add_item(&Rmotion, &on_Rmotion_selected);
  suMenu.add_item(&FreeMem, &on_FreeMem_selected);
  //Root menu (always last)  
  ms.set_root_menu(&mm);

  Serial.println("Menu system initialized");
  displayMenu();
}

/////////////////////////////////////////////////////////////////////////////////
// Callback functions
/////////////////////////////////////////////////////////////////////////////////
void on_videoTime_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading("Set video time");
    displayNumericSetInstructions();
    
    tempVideoTimeSetting = (float)videoTimeSetting;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  if( adjustNumericValue(&tempVideoTimeSetting,5,1800,true) )  // 5 seconds to 30 minutes
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

void on_shootTime_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.clear();
    displaySetHeading("Set shoot time");
    displayNumericSetInstructions();
    
    tempShootTimeSetting = (float)shootTimeSetting;  // save a copy of the current setting in case we cancel
  }

  // callback function main:
  if( adjustNumericValue(&tempShootTimeSetting,300,2592000,true) )  //5 minutes to 30 days
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

void on_pm_autoMode_selected(MenuItem* p_menu_item)
{
  Serial.print("pma ");
  lcd.setCursor(0,1);
  lcd.print("Pano Mode = AUTO");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  displayMenu();
}

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
  //  Serial.print("Inside the motion profile menu, ");
  lcd.setCursor(0,1);
  lcd.print("Motion = SPLINE");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  waitForCbutton();
}

void on_Xmotion_selected(MenuItem* p_menu_item)
{
  //  Serial.print("Inside the on_Xmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("Enabled");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  waitForCbutton();
}

void on_Ymotion_selected(MenuItem* p_menu_item)
{
  //  Serial.print("Inside the on_Ymotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("Enabled");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  waitForCbutton();
}

void on_Zmotion_selected(MenuItem* p_menu_item)
{
  //  Serial.print("Inside the on_Zmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("disabled");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  waitForCbutton();
}

void on_Dmotion_selected(MenuItem* p_menu_item)
{
  //  Serial.print("Inside the on_Dmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("disabled");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  waitForCbutton();
}

void on_Rmotion_selected(MenuItem* p_menu_item)
{
  //  Serial.print("Inside the on_Rmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("Disabled");
  if(nunchuk.userInput == 'C') ms.deselect_set_menu_item();
  //  waitForCbutton();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// FREE MEMORY Display
///////////////////////////////////////////////////////////////////////////////////////////////////
void on_FreeMem_selected(MenuItem* p_menu_item)
{
  // callback function "constructor"
  if (ms.menu_item_was_just_selected())
  {
    lcd.setCursor(0,1);
    lcd.print("Free Memory =");
  }

  // callback function main:
  lcd.setCursor(15,1);
  lcd.print(freeMemory(),DEC); 
  lcd.print("  ");

  // callback function "destructor"
  if(nunchuk.userInput == 'C')
  {
    ms.deselect_set_menu_item();
    displayMenu();
  }
}


