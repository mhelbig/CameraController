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
MenuItem calZoomMin         ("Calibrate Zoom Min");
MenuItem calZoomMax         ("Calibrate Zoom Max");
MenuItem setExposureTime    ("Camera Shutter Time");
MenuItem transitionToSet    ("Select transition");
MenuItem setVideoTime       ("Set video time");
MenuItem setPanTilt         ("Set pan/tilt");
MenuItem setZoomSlide       ("Set zoom/slide");
MenuItem setRotateSteps     ("Set Rotate");
MenuItem addTransition      ("Add transition");
MenuItem delTransition      ("Delete transition");
MenuItem setShootTime       ("Set shoot time");
MenuItem dryRun             ("Dry Run");
MenuItem setStartDelay      ("Set start delay");
MenuItem RunSequence        ("Run sequence");

//panoramic menu
Menu pmMenu                 ("360 Panograph");
MenuItem pm_autoMode        ("Panograph Auto");

//Setup menu
Menu suMenu                 ("System Settings");
MenuItem loadMotorPos       ("Load last sequence");
//MenuItem saveMotorPos       ("Save Sequence");
MenuItem backlightTime      ("Backlight Time");
MenuItem lensDefoggerPWM    ("Lens defogger power");
MenuItem lensDefoggerMode   ("Lens defogger mode");
MenuItem framesPerSecond    ("Video frames/sec");
MenuItem shutterButtonTime  ("Shutter button time");
MenuItem cameraRecoveryTime ("Camera Save time");
MenuItem motorSettleTime    ("Motor settle time");
MenuItem motionProfile      ("Motion Profile");
MenuItem XmotorInvert       ("X motor direction");
MenuItem XmotorEnable       ("X motor enable");
MenuItem XmotorPulsesPerRev ("X motor pulses/rev");
MenuItem YmotorInvert       ("Y motor direction");
MenuItem YmotorEnable       ("Y motor enable");
MenuItem ZmotorInvert       ("Z motor direction");
MenuItem ZmotorEnable       ("Z motor enable");
MenuItem DmotorInvert       ("D motor direction");
MenuItem DmotorEnable       ("D motor enable");
MenuItem RmotorInvert       ("R motor direction");
MenuItem RmotorEnable       ("R motor enable");
MenuItem RmotorPulsesPerRev ("R motor pulses/rev");
MenuItem loadSettings       ("Load settings");
MenuItem saveSettings       ("Save settings");
MenuItem restoreDefaults    ("Restore defaults");
MenuItem FreeMem            ("System Free Memory");

/////////////////////////////////////////////////////////////////////////////////
// Initialize
/////////////////////////////////////////////////////////////////////////////////
void initializeMenu(void)
{
//Timelapse menu
  mm.add_menu(&tlMenu);
  tlMenu.add_item(&calZoomMin,       &on_calZoomMin_selected);
  tlMenu.add_item(&calZoomMax,       &on_calZoomMax_selected);
  tlMenu.add_item(&setExposureTime,  &on_setExposureTime_selected);
  tlMenu.add_item(&transitionToSet,  &on_transitionToSet_selected);
  tlMenu.add_item(&setVideoTime,     &on_set_videoTime_selected);
  tlMenu.add_item(&setPanTilt,       &on_setPanTilt_selected);
  tlMenu.add_item(&setZoomSlide,     &on_setZoomSlide_selected);
  tlMenu.add_item(&setRotateSteps,   &on_setRotateSteps_selected);
  tlMenu.add_item(&addTransition,    &on_addTransition_selected);
  tlMenu.add_item(&delTransition,    &on_delTransition_selected);
  tlMenu.add_item(&setShootTime,     &on_set_shootTime_selected);
  tlMenu.add_item(&dryRun,           &on_dryRun_selected);
  tlMenu.add_item(&setStartDelay,    &on_setStartDelay_selected);
  tlMenu.add_item(&RunSequence,      &on_RunSequence_selected);

//Panoramic menu
//  mm.add_menu(&pmMenu);
//  pmMenu.add_item(&pm_autoMode, &on_pm_autoMode_selected);

//Setup menu
  mm.add_menu(&suMenu);
  suMenu.add_item(&loadMotorPos,       &on_loadMotorPositions_selected);
//  suMenu.add_item(&saveMotorPos,       &on_saveMotorPositions_selected);  // motor positions are now automatically saved when we do a run sequence
  suMenu.add_item(&backlightTime,      &on_backlightTime_selected);
  suMenu.add_item(&lensDefoggerPWM,    &on_lensDefoggerPWM_selected);
  suMenu.add_item(&lensDefoggerMode,   &on_lensDefoggerMode_selected);
  suMenu.add_item(&framesPerSecond,    &on_framesPerSecond_selected);
  suMenu.add_item(&shutterButtonTime,  &on_shutterButtonTime_selected);
  suMenu.add_item(&cameraRecoveryTime, &on_cameraRecoveryTime_selected);
  suMenu.add_item(&motorSettleTime,    &on_motorSettleTime_Selected);
  suMenu.add_item(&motionProfile,      &on_motionProfile_selected);
  suMenu.add_item(&XmotorInvert,       &on_XmotorInvert_selected);
  suMenu.add_item(&XmotorEnable,       &on_XmotorEnable_selected);
  suMenu.add_item(&XmotorPulsesPerRev, &on_XmotorPulsesPerRev_selected);
  suMenu.add_item(&YmotorInvert,       &on_YmotorInvert_selected);
  suMenu.add_item(&YmotorEnable,       &on_YmotorEnable_selected);
  suMenu.add_item(&ZmotorInvert,       &on_ZmotorInvert_selected);
  suMenu.add_item(&ZmotorEnable,       &on_ZmotorEnable_selected);
  suMenu.add_item(&DmotorInvert,       &on_DmotorInvert_selected);
  suMenu.add_item(&DmotorEnable,       &on_DmotorEnable_selected);
  suMenu.add_item(&RmotorInvert,       &on_RmotorInvert_selected);
  suMenu.add_item(&RmotorEnable,       &on_RmotorEnable_selected);
  suMenu.add_item(&RmotorPulsesPerRev, &on_RmotorPulsesPerRev_selected);
  suMenu.add_item(&saveSettings,       &on_saveNonVolatileSettings_selected);
  suMenu.add_item(&loadSettings,       &on_loadNonVolatileSettings_selected);
  suMenu.add_item(&restoreDefaults,    &on_restoreNonVolatileSettings_selected);
  suMenu.add_item(&FreeMem,            &on_FreeMem_selected);

//Root menu (always last)  
  ms.set_root_menu(&mm);

  Serial.println("Menu system initialized");
  displayMenu();
}

