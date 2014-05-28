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
// M = Motion detected (from accelerometer)

void initializeNavchuk(void)
{
  nunchuk.init();
  Serial.println("Nunchuk input device initialized");
}

void waitForCbutton(void)
{
  displaySetInstructions();
  do
  {
    nunchuk.update();
  } while(nunchuk.userInput !='C' && nunchuk.userInput !='Z');
//  ms.next();
}  

