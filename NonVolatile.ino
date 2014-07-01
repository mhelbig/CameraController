/////////////////////////////////////////////////////////////////////////////////
// initialize EEPROM NonVolatile Storage Addresses
/////////////////////////////////////////////////////////////////////////////////
int selectedExposureIndexAddress      = EEPROM.getAddress(sizeof(int));
int shutterButtonTimeSettingAddress   = EEPROM.getAddress(sizeof(int));
int cameraRecoveryTimeSettingAddress  = EEPROM.getAddress(sizeof(int));
int motorSettleTimeSettingAddress     = EEPROM.getAddress(sizeof(int));
int videoFramesPerSecondIndexAddress  = EEPROM.getAddress(sizeof(int));
int selectedMotionProfileIndexAddress = EEPROM.getAddress(sizeof(int));

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
