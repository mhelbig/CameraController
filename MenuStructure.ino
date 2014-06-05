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
Menu mm("    PanTron 4000");

//Timelapse menu
Menu tlMenu                 ("Timelapse Video");
MenuItem transitionToSet    ("Transition to set");
MenuItem setPositions       ("Set positions");
MenuItem setVideoTime       ("Set video time");
MenuItem addDelTransition   ("Add/Del transition");
MenuItem setShootTime       ("Set shoot time");
MenuItem setStartDelay      ("Set start delay");
MenuItem systemReady        ("System ready");
MenuItem countdownToStart   ("Countdown to start");
MenuItem runningSequence    ("Running sequence");

//panoramic menu
Menu pmMenu                 ("360 Panograph");
MenuItem pm_autoMode        ("Panograph Auto");

//Setup menu
Menu suMenu                 ("Change Settings");
MenuItem framesPerSecond    ("Frames/sec");
MenuItem motionProfile      ("Motion Profile");
MenuItem FreeMem            ("Free Memory");

/////////////////////////////////////////////////////////////////////////////////
// Initialize
/////////////////////////////////////////////////////////////////////////////////
void initializeMenu(void)
{
//Timelapse menu
  mm.add_menu(&tlMenu);
//  tlMenu.add_item(&transitionToSet,  &on_transitionToSet_selected);
//  tlMenu.add_item(&setPositions,     &on_setPositions_selected);
  tlMenu.add_item(&setVideoTime,     &on_set_videoTime_selected);
//  tlMenu.add_item(&addDelTransition, &on_addDelTransition_selected;
  tlMenu.add_item(&setShootTime,     &on_set_shootTime_selected);
//  tlMenu.add_item(&setStartDelay,    &on_setStartDelay_selected);
//  tlMenu.add_item(&systemReady,      &on_systemReady_selected);
//  tlMenu.add_item(&countdownToStart, &on_coundownToStart_selected);
//  tlMenu.add_item(&runningSequence,  &on_runningSequence_selected);

//Panoramic menu
  mm.add_menu(&pmMenu);
  pmMenu.add_item(&pm_autoMode, &on_pm_autoMode_selected);

//Setup menu
  mm.add_menu(&suMenu);
  suMenu.add_item(&framesPerSecond, &on_framesPerSecond_selected);
  suMenu.add_item(&motionProfile, &on_motionProfile_selected);
  suMenu.add_item(&FreeMem, &on_FreeMem_selected);

//Root menu (always last)  
  ms.set_root_menu(&mm);

  Serial.println("Menu system initialized");
  displayMenu();
}

