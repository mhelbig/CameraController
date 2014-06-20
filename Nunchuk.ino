/////////////////////////////////////////////////////////////////////////////////
// Nunchuk return code reference:
//
// N = Null (no movement)
// F = joystick forward
// B = joystick backward
// L = joystick left
// R = joystick right
// C = Button C
// Z = Button Z
// Lowercase version of any of the above characters indicates function held active for a while
// above keys will repeat at the repeat rate after the repeat delay

// M = Motion detected (from accelerometer)
// I = Nunchuk idle (no accelerometer action detected for a while)

void initializeNavchuk(void)
{
  nunchuk.init();
  Serial.println("Nunchuk input device initialized");
}

