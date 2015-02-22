#define FOCUS_PIN           A3
#define SHUTTER_PIN         A4

void pressShutterButton(void)
{
  digitalWrite(SHUTTER_PIN,HIGH);
  lcd.setCursor(19,0);
  lcd.print("S");
}

void releaseShutterButton(void)
{
  digitalWrite(SHUTTER_PIN,LOW);
  lcd.setCursor(19,0);
  lcd.print(" ");
}

void pressFocusButton(void)
{
  digitalWrite(FOCUS_PIN,HIGH);
  lcd.setCursor(18,0);
  lcd.print("F");
}

void releaseFocusButton(void)
{
  digitalWrite(FOCUS_PIN,LOW);
  lcd.setCursor(18,0);
  lcd.print(" ");
}

void initializeShutterControl(void)
{
  digitalWrite(FOCUS_PIN,LOW);
  digitalWrite(SHUTTER_PIN,LOW);

  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
}

