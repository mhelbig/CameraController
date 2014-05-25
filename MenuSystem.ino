// Establish the input device
Navchuk nunchuk = Navchuk();

/////////////////////////////////////////////////////////////////////////////////
// General menu functions and behavior
/////////////////////////////////////////////////////////////////////////////////
void navigationHandler() 
{
  do
  {
    nunchuk.update();
    lcd.setBacklight(!nunchuk.isIdle);  // <--- we need to make this edge sensitive and work in all menu locations
    delay(10);  // we need this delay, otherwise the nunchuk gets garbage data from this lcd.write for some reason
  } while(nunchuk.userInput ==' ');

  switch (nunchuk.userInput)
  {
  case 'F': // forward selected - go up the menu tree
      Serial.print("ms.prev function starting, ");
      ms.prev();
      displayMenu();
      Serial.println("ms.prev function completed");
      break;
  case 'B': // back selected - go down the menu tree
      Serial.print("ms.next function starting, ");      ms.next();
      displayMenu();
      Serial.println("ms.next function completed");
    break;
  case 'L': // left selected - back out of menu
      Serial.print("ms.back function starting, ");
      ms.back();
      displayMenu();
      Serial.println("ms.back function completed");
    break;
  case 'R': // right selected - drop into submenu
      Serial.print("ms.select function starting, ");
      ms.select(0);
      displayMenu();
      Serial.println("ms.select function completed");
    break;
  case 'C': // Not assigned - used inside menus for cancelling last adjustment
    Serial.println("'C' pressed, no menu function assigned");
    break;
  case 'Z': // Not assigned - used inside menus for accepting last adjustment
    Serial.print("'Z' pressed, no menu function assigned");  Serial.println(millis());
    break;
  case 'c': // Not assigned, C button held
//    Serial.println("'C' Held");
    break;
  case 'z': // Not assigned, C button held
    Serial.print("'Z' Held");  Serial.println(millis());
    break;
  default:
    break;
  }
}

void displaySetInstructions(void)
{
  lcd.setCursor(0,2);
  lcd.print(" Joystick = Adjust");

  lcd.setCursor(0,3);
  lcd.print("C=Cancel       Z=Set");
}

// Display the menu headings and current selection
void displayMenu()
{
  Serial.print("displaying menu, ");
  Menu const* cp_menu = ms.get_current_menu();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(cp_menu->get_selected()->get_name());
}
