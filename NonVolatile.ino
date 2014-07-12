/////////////////////////////////////////////////////////////////////////////////
// assign EEPROM NonVolatile Storage Addresses
/////////////////////////////////////////////////////////////////////////////////
// Setup menu parameters:
int selectedExposureIndexAddress      = EEPROM.getAddress(sizeof(int));
int shutterButtonTimeSettingAddress   = EEPROM.getAddress(sizeof(int));
int postShootTimeDelaySettingAddress  = EEPROM.getAddress(sizeof(int));
int cameraRecoveryTimeSettingAddress  = EEPROM.getAddress(sizeof(int));
int motorSettleTimeSettingAddress     = EEPROM.getAddress(sizeof(int));
int videoFramesPerSecondIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedMotionProfileIndexAddress = EEPROM.getAddress(sizeof(int));
int selectedXmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedYmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedZmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedDmotorInvertIndexAddress  = EEPROM.getAddress(sizeof(int));

//motor position values to optionally store:
int numberOfTransitionsAddress        = EEPROM.getAddress(sizeof(int));
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
  EEPROM.writeInt(selectedExposureIndexAddress,       selectedExposureIndex);
  EEPROM.writeInt(shutterButtonTimeSettingAddress,    shutterButtonTimeSetting);
  EEPROM.writeInt(postShootTimeDelaySettingAddress,   postShootTimeDelaySetting);
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
  selectedExposureIndex       = EEPROM.readInt(selectedExposureIndexAddress);
  shutterButtonTimeSetting    = EEPROM.readInt(shutterButtonTimeSettingAddress);
  postShootTimeDelaySetting   = EEPROM.readInt(postShootTimeDelaySettingAddress);
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
  selectedExposureIndex       = 5;
  shutterButtonTimeSetting    = 100;
  postShootTimeDelaySetting   = 100;
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
// Save motor position arrays
/////////////////////////////////////////////////////////////////////////////////
void saveMotorPositions(void)
{
  EEPROM.writeInt  (numberOfTransitionsAddress, numberOfTransitions);
  EEPROM.writeBlock(frameNumberPointsAddress,   frameNumber,          MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(XmotorSplinePointsAddress,  XmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(YmotorSplinePointsAddress,  YmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(ZmotorSplinePointsAddress,  ZmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(DmotorSplinePointsAddress,  DmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);

  EEPROM.writeFloat(ZmotorMinPositionAddress,   ZmotorMinPosition);
  EEPROM.writeFloat(ZmotorMaxPositionAddress,   ZmotorMaxPosition);
  EEPROM.writeFloat(DmotorMinPositionAddress,   DmotorMinPosition);
  EEPROM.writeFloat(DmotorMaxPositionAddress,   DmotorMaxPosition);
}

/////////////////////////////////////////////////////////////////////////////////
// Load motor position arrays
/////////////////////////////////////////////////////////////////////////////////
void loadMotorPositions(void)
{
  numberOfTransitions  = EEPROM.readInt(numberOfTransitionsAddress);
  EEPROM.readBlock(frameNumberPointsAddress,  frameNumber,           MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(XmotorSplinePointsAddress, XmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(YmotorSplinePointsAddress, YmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(ZmotorSplinePointsAddress, ZmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(DmotorSplinePointsAddress, DmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
}
