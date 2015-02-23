#define FOCUS_PIN           A3
#define SHUTTER_PIN         A4

void pressShutterButton(void)
{
  digitalWrite(SHUTTER_PIN,HIGH);
  lcd.setCursor(17,3);
  lcd.print("_");
}

void releaseShutterButton(void)
{
  digitalWrite(SHUTTER_PIN,LOW);
  lcd.setCursor(17,3);
  lcd.print("S");
}

void pressFocusButton(void)
{
  digitalWrite(FOCUS_PIN,HIGH);
  lcd.setCursor(16,3);
  lcd.print("_");
}

void releaseFocusButton(void)
{
  digitalWrite(FOCUS_PIN,LOW);
  lcd.setCursor(16,3);
  lcd.print("F");
}

void initializeShutterControl(void)
{
  digitalWrite(FOCUS_PIN,LOW);
  digitalWrite(SHUTTER_PIN,LOW);

  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
}

