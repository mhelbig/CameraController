//When adding menu components, add them to each of the three sections:
//
//  Menu structure:   Defines the names for each menu item which is displayed on the LCD
//  initialize:       Adds each item to the menu structure
//  Callback:         Associates each selectable menu item to a function

/////////////////////////////////////////////////////////////////////////////////
// Menu structure
/////////////////////////////////////////////////////////////////////////////////
//Root menu
MenuSystem ms;
Menu mm("Camera Controller");
//Timelapse menu
Menu tlMenu("Timelapse Mode");
MenuItem shootTime("Shoot time");
//panoramic menu
Menu pmMenu("360 Panograph Mode");
MenuItem pm_autoMode("Panograph Auto");
//Setup menu
Menu suMenu("System Settings");
MenuItem framesPerSecond("Frames/sec");
MenuItem motionProfile("Motion Profile");
MenuItem Xmotion("X (Pan) Motion");
MenuItem Ymotion("Y (Tilt) Motion");
MenuItem Zmotion("Z (Zoom) Motion");
MenuItem Dmotion("D (Dolly) Motion");
MenuItem Rmotion("R (Rotate) Motion");

/////////////////////////////////////////////////////////////////////////////////
// Initialize
/////////////////////////////////////////////////////////////////////////////////
void initializeMenu(void)
{
//Timelapse menu
  mm.add_menu(&tlMenu);
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
//Root menu (always last)  
  ms.set_root_menu(&mm);

  Serial.println("Menu system initialized");
  displayMenu();
}

/////////////////////////////////////////////////////////////////////////////////
// Callback functions
/////////////////////////////////////////////////////////////////////////////////
void on_shootTime_selected(MenuItem* p_menu_item)
{
  Serial.print("st ");
  lcd.setCursor(0,1);
  lcd.print("Shoot time = 1 hr");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
  displayMenu();
}

void on_pm_autoMode_selected(MenuItem* p_menu_item)
{
  Serial.print("pma ");
  lcd.setCursor(0,1);
  lcd.print("Pano Mode = AUTO");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
  displayMenu();
}

void on_framesPerSecond_selected(MenuItem* p_menu_item)
{
  Serial.print("fps ");
  lcd.setCursor(0,1);
  lcd.print("Frames/sec = 30");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
  displayMenu();
}

void on_motionProfile_selected(MenuItem* p_menu_item)
{
//  Serial.print("Inside the motion profile menu, ");
  lcd.setCursor(0,1);
  lcd.print("Motion = SPLINE");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
//  waitForCbutton();
}

void on_Xmotion_selected(MenuItem* p_menu_item)
{
//  Serial.print("Inside the on_Xmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("Enabled");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
//  waitForCbutton();
}

void on_Ymotion_selected(MenuItem* p_menu_item)
{
//  Serial.print("Inside the on_Ymotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("Enabled");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
//  waitForCbutton();
}

void on_Zmotion_selected(MenuItem* p_menu_item)
{
//  Serial.print("Inside the on_Zmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("disabled");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
//  waitForCbutton();
}

void on_Dmotion_selected(MenuItem* p_menu_item)
{
//  Serial.print("Inside the on_Dmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("disabled");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
//  waitForCbutton();
}

void on_Rmotion_selected(MenuItem* p_menu_item)
{
//  Serial.print("Inside the on_Rmotion menu, ");
  lcd.setCursor(0,1);
  lcd.print("Disabled");
  if(nunchuk.userInput == 'C') ms.set_menu_item_selected(false);
//  waitForCbutton();
}