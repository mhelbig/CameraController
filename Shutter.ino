#define FOCUS_PIN           A3
#define SHUTTER_PIN         A4

void pressShutterButton(void)
{
  digitalWrite(SHUTTER_PIN,HIGH);
}

void releaseShutterButton(void)
{
  digitalWrite(SHUTTER_PIN,LOW);
}

void pressFocusButton(void)
{
  digitalWrite(FOCUS_PIN,HIGH);
}

void releaseFocusButton(void)
{
  digitalWrite(FOCUS_PIN,LOW);
}

void initializeShutterControl(void)
{
  digitalWrite(FOCUS_PIN,LOW);
  digitalWrite(SHUTTER_PIN,LOW);

  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
}

