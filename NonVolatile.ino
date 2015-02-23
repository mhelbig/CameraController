/////////////////////////////////////////////////////////////////////////////////
// assign EEPROM NonVolatile Storage Addresses
/////////////////////////////////////////////////////////////////////////////////
// Setup menu parameters:
int lensDefoggerPWMsettingAddress     = EEPROM.getAddress(sizeof(int));
int lensDefoggerModeIndexAddress      = EEPROM.getAddress(sizeof(int));
int selectedExposureIndexAddress      = EEPROM.getAddress(sizeof(int));
int shutterButtonTimeSettingAddress   = EEPROM.getAddress(sizeof(int));
int backlightTimeIndexAddress         = EEPROM.getAddress(sizeof(int));
int cameraRecoveryTimeSettingAddress  = EEPROM.getAddress(sizeof(int));
int motorSettleTimeSettingAddress     = EEPROM.getAddress(sizeof(int));
int videoFramesPerSecondIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedMotionProfileIndexAddress = EEPROM.getAddress(sizeof(int));
int selectedXmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedYmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedZmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedDmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));

// saved sequence values:
int numberOfTransitionsAddress        = EEPROM.getAddress(sizeof(int));
int shootTimeSettingAddress           = EEPROM.getAddress(sizeof(float));
int startDelayTimeSettingAddress      = EEPROM.getAddress(sizeof(float));
int frameNumberPointsAddress          = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));
int XmotorSplinePointsAddress         = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));
int YmotorSplinePointsAddress         = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));
int ZmotorSplinePointsAddress         = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));
int DmotorSplinePointsAddress         = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));
int ZmotorMinPositionAddress          = EEPROM.getAddress(sizeof(float));
int ZmotorMaxPositionAddress          = EEPROM.getAddress(sizeof(float));
int DmotorMinPositionAddress          = EEPROM.getAddress(sizeof(float));
int DmotorMaxPositionAddress          = EEPROM.getAddress(sizeof(float));

/////////////////////////////////////////////////////////////////////////////////
// Save Settings
/////////////////////////////////////////////////////////////////////////////////
void saveNonVolatileSettings(void)
{
  EEPROM.writeInt(lensDefoggerPWMsettingAddress,      lensDefoggerPWMsetting);
  EEPROM.writeInt(lensDefoggerModeIndexAddress,       lensDefoggerModeIndex);
  EEPROM.writeInt(selectedExposureIndexAddress,       selectedExposureIndex);
  EEPROM.writeInt(shutterButtonTimeSettingAddress,    shutterButtonTimeSetting);
  EEPROM.writeInt(backlightTimeIndexAddress,          backlightTimeIndex);
  EEPROM.writeInt(cameraRecoveryTimeSettingAddress,   cameraRecoveryTimeSetting);
  EEPROM.writeInt(videoFramesPerSecondIndexAddress,   videoFramesPerSecondIndex);
  EEPROM.writeInt(motorSettleTimeSettingAddress,      motorSettleTimeSetting);
  EEPROM.writeInt(selectedMotionProfileIndexAddress,  selectedMotionProfileIndex);
  
  EEPROM.writeInt(selectedXmotorInvertIndexAddress,   selectedXmotorInvertIndex);  
  EEPROM.writeInt(selectedYmotorInvertIndexAddress,   selectedYmotorInvertIndex);  
  EEPROM.writeInt(selectedZmotorInvertIndexAddress,   selectedZmotorInvertIndex);  
  EEPROM.writeInt(selectedDmotorInvertIndexAddress,   selectedDmotorInvertIndex);  
}

/////////////////////////////////////////////////////////////////////////////////
// Load Settings
/////////////////////////////////////////////////////////////////////////////////
void loadNonVolatileSettings(void)
{
  lensDefoggerPWMsetting      = EEPROM.readInt(lensDefoggerPWMsettingAddress);
  lensDefoggerModeIndex       = EEPROM.readInt(lensDefoggerModeIndexAddress);
  selectedExposureIndex       = EEPROM.readInt(selectedExposureIndexAddress);
  shutterButtonTimeSetting    = EEPROM.readInt(shutterButtonTimeSettingAddress);
  backlightTimeIndex          = EEPROM.readInt(backlightTimeIndexAddress);
  cameraRecoveryTimeSetting   = EEPROM.readInt(cameraRecoveryTimeSettingAddress);
  videoFramesPerSecondIndex   = EEPROM.readInt(videoFramesPerSecondIndexAddress);
  motorSettleTimeSetting      = EEPROM.readInt(motorSettleTimeSettingAddress);
  selectedMotionProfileIndex  = EEPROM.readInt(selectedMotionProfileIndexAddress);

  selectedXmotorInvertIndex   = EEPROM.readInt(selectedXmotorInvertIndexAddress);
  selectedYmotorInvertIndex   = EEPROM.readInt(selectedYmotorInvertIndexAddress);
  selectedZmotorInvertIndex   = EEPROM.readInt(selectedZmotorInvertIndexAddress);
  selectedDmotorInvertIndex   = EEPROM.readInt(selectedDmotorInvertIndexAddress);
}

/////////////////////////////////////////////////////////////////////////////////
// Restore Default Settings
/////////////////////////////////////////////////////////////////////////////////
void restoreDefaultSettings(void)
{
  lensDefoggerPWMsetting      = 50;
  lensDefoggerModeIndex       = 0;
  selectedExposureIndex       = 21;
  shutterButtonTimeSetting    = 100;
  backlightTimeIndex          = 1;
  cameraRecoveryTimeSetting   = 200;
  motorSettleTimeSetting      = 250;
  videoFramesPerSecondIndex   = 2;
  selectedMotionProfileIndex  = 2;
  selectedXmotorInvertIndex   = 0;
  selectedYmotorInvertIndex   = 0;
  selectedZmotorInvertIndex   = 0;
  selectedDmotorInvertIndex   = 0;
  ZmotorMinPosition = 0;
  ZmotorMaxPosition = 0;
  DmotorMinPosition = 0;
  DmotorMaxPosition = 0;
}

/////////////////////////////////////////////////////////////////////////////////
// Save sequence
/////////////////////////////////////////////////////////////////////////////////
void saveMotorPositions(void)
{
  EEPROM.writeInt(numberOfTransitionsAddress,     numberOfTransitions);
  EEPROM.writeInt(selectedExposureIndexAddress,   selectedExposureIndex);
  EEPROM.writeFloat(shootTimeSettingAddress,      shootTimeSetting);
  EEPROM.writeFloat(startDelayTimeSettingAddress, startDelayTimeSetting);
  
  EEPROM.writeFloat(ZmotorMinPositionAddress,     ZmotorMinPosition);
  EEPROM.writeFloat(ZmotorMaxPositionAddress,     ZmotorMaxPosition);
  EEPROM.writeFloat(DmotorMinPositionAddress,     DmotorMinPosition);
  EEPROM.writeFloat(DmotorMaxPositionAddress,     DmotorMaxPosition);

  EEPROM.writeBlock(frameNumberPointsAddress,     frameNumber,          MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(XmotorSplinePointsAddress,    XmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(YmotorSplinePointsAddress,    YmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(ZmotorSplinePointsAddress,    ZmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(DmotorSplinePointsAddress,    DmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);

}

/////////////////////////////////////////////////////////////////////////////////
// Load sequence
/////////////////////////////////////////////////////////////////////////////////
void loadMotorPositions(void)
{
  numberOfTransitions         = EEPROM.readInt(numberOfTransitionsAddress);
  selectedExposureIndex       = EEPROM.readInt(selectedExposureIndexAddress);
  shootTimeSetting            = EEPROM.readFloat(shootTimeSettingAddress);
  startDelayTimeSetting       = EEPROM.readFloat(startDelayTimeSettingAddress);
  
  ZmotorMinPosition           = EEPROM.readFloat(ZmotorMinPositionAddress);
  ZmotorMaxPosition           = EEPROM.readFloat(ZmotorMaxPositionAddress);
  DmotorMinPosition           = EEPROM.readFloat(DmotorMinPositionAddress);
  DmotorMaxPosition           = EEPROM.readFloat(DmotorMaxPositionAddress);
  
  EEPROM.readBlock(frameNumberPointsAddress,  frameNumber,           MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(XmotorSplinePointsAddress, XmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(YmotorSplinePointsAddress, YmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(ZmotorSplinePointsAddress, ZmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(DmotorSplinePointsAddress, DmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
}
