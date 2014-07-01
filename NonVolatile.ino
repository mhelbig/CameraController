/////////////////////////////////////////////////////////////////////////////////
// initialize EEPROM NonVolatile Storage Addresses
/////////////////////////////////////////////////////////////////////////////////
int selectedExposureIndexAddress      = EEPROM.getAddress(sizeof(int));
int shutterButtonTimeSettingAddress   = EEPROM.getAddress(sizeof(int));
int cameraRecoveryTimeSettingAddress  = EEPROM.getAddress(sizeof(int));
int motorSettleTimeSettingAddress     = EEPROM.getAddress(sizeof(int));
int videoFramesPerSecondIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedMotionProfileIndexAddress = EEPROM.getAddress(sizeof(int));
//motor position values to optionally store:
int numberOfTransitionsAddress        = EEPROM.getAddress(sizeof(int));
int frameNumberPointsAddress          = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));
int XmotorSplinePointsAddress         = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));
int YmotorSplinePointsAddress         = EEPROM.getAddress(sizeof(float) * (MAX_NUMBER_OF_TRANSITIONS + 2));

void saveNonVolatileSettings(void)
{
  EEPROM.writeInt(selectedExposureIndexAddress,      selectedExposureIndex);
  EEPROM.writeInt(shutterButtonTimeSettingAddress,   shutterButtonTimeSetting);
  EEPROM.writeInt(cameraRecoveryTimeSettingAddress,  cameraRecoveryTimeSetting);
  EEPROM.writeInt(videoFramesPerSecondIndexAddress,  videoFramesPerSecondIndex);
  EEPROM.writeInt(motorSettleTimeSettingAddress,     motorSettleTimeSetting);
  EEPROM.writeInt(selectedMotionProfileIndexAddress, selectedMotionProfileIndex);
}

void loadNonVolatileSettings(void)
{
  selectedExposureIndex       = EEPROM.readInt(selectedExposureIndexAddress);
  shutterButtonTimeSetting    = EEPROM.readInt(shutterButtonTimeSettingAddress);
  cameraRecoveryTimeSetting   = EEPROM.readInt(cameraRecoveryTimeSettingAddress);
  videoFramesPerSecondIndex   = EEPROM.readInt(videoFramesPerSecondIndexAddress);
  motorSettleTimeSetting      = EEPROM.readInt(motorSettleTimeSettingAddress);
  selectedMotionProfileIndex  = EEPROM.readInt(selectedMotionProfileIndexAddress);
}

void restoreDefaultSettings(void)
{
  selectedExposureIndex       = 5;
  shutterButtonTimeSetting    = 100;
  cameraRecoveryTimeSetting   = 200;
  motorSettleTimeSetting      = 250;
  videoFramesPerSecondIndex   = 2;
  selectedMotionProfileIndex  = 2;
}

void saveMotorPositions(void)
{
  EEPROM.writeInt  (numberOfTransitionsAddress, numberOfTransitions);
  EEPROM.writeBlock(frameNumberPointsAddress,   frameNumber,          MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(XmotorSplinePointsAddress,  XmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.writeBlock(YmotorSplinePointsAddress,  YmotorSplinePoints_y, MAX_NUMBER_OF_TRANSITIONS + 2);
}

void loadMotorPositions(void)
{
  numberOfTransitions  = EEPROM.readInt(numberOfTransitionsAddress);
  EEPROM.readBlock(frameNumberPointsAddress,  frameNumber,           MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(XmotorSplinePointsAddress, XmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
  EEPROM.readBlock(YmotorSplinePointsAddress, YmotorSplinePoints_y,  MAX_NUMBER_OF_TRANSITIONS + 2);
}
