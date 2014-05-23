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
  } while(nunchuk.userInput ==' ' || nunchuk.userInput == 'M');
  
  switch (nunchuk.userInput)
  {
  case 'F': // forward selected - go up the menu tree
      ms.prev();
      displayMenu();
      break;
  case 'B': // back selected - go down the menu tree
      ms.next();
      displayMenu();
    break;
  case 'L': // left selected - back out of menu
      ms.back();
      displayMenu();
    break;
  case 'R': // right selected - drop into submenu
      ms.select(0);
      displayMenu();
    break;
  case 'C': // Not assigned - used inside menus for cancelling last adjustment
    break;
  case 'Z': // Not assigned - used inside menus for accepting last adjustment
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
  Menu const* cp_menu = ms.get_current_menu();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(cp_menu->get_selected()->get_name());
}
