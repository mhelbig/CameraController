// Menu variables
MenuSystem ms;
Menu mm("Camera Controller");
Menu tlMenu("Timelapse Mode");
MenuItem tl_framesPerSecond("Set # frames/sec");
MenuItem tl_shootTime("Set shoot time");
MenuItem tl_motionProfile("Set motion profile");
Menu pmMenu("Panograph Mode");
MenuItem pm_autoMode("Panograph Auto");

/////////////////////////////////////////////////////////////////////////////////
// Associated menu callback functions
/////////////////////////////////////////////////////////////////////////////////
void on_item1_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Frames/sec = 30");
  waitForCbutton();
}

void on_item2_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Shoot time = 1 hr");
  waitForCbutton();
}

void on_item3_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Motion = SPLINE");
  waitForCbutton();
}

void on_item4_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Pano Mode = AUTO");
  waitForCbutton();
}

void displayMenu()
{
  lcd.clear();
  lcd.setCursor(0,0);
  // Display the menu
  Menu const* cp_menu = ms.get_current_menu();

  //lcd.print("Current menu name: ");
  lcd.print(cp_menu->get_name());
  
  lcd.setCursor(0,1);
  
  lcd.print(cp_menu->get_selected()->get_name());
}

void initializeMenu(void)
{
  mm.add_menu(&tlMenu);
  tlMenu.add_item(&tl_framesPerSecond, &on_item1_selected);
  tlMenu.add_item(&tl_shootTime, &on_item2_selected);
  tlMenu.add_item(&tl_motionProfile, &on_item3_selected);
  mm.add_menu(&pmMenu);
  pmMenu.add_item(&pm_autoMode, &on_item4_selected);
  ms.set_root_menu(&mm);

  Serial.println("Menu system initialized");
  displayMenu();
}
