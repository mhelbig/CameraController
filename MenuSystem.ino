/////////////////////////////////////////////////////////////////////////////////
// General menu functions and behavior
/////////////////////////////////////////////////////////////////////////////////
void navigationHandler() 
{
  nunchuk.update();
   if(nunchuk.userInput == 'M') // Nunchuk is moving, turn on the backlighting
       lcd.setBacklight(true);
   if(nunchuk.userInput == 'I') // Nunchuk is idle, turn off the backlighting
       lcd.setBacklight(false);

  if(ms.menu_item_is_selected())
  {
    ms.select(0);
  }
  else
  {
    switch (nunchuk.userInput)
    {
    case ' ': // nothing selected
      break;
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
    case 'R': // right selected - drop into submenu or menu item
      if(ms.select())
        displayMenu();
      break;
    case 'C': // Not assigned - used inside menus for cancelling last adjustment
      Serial.println("'C' pressed, no menu function assigned");
      break;
    case 'Z': // Not assigned - used inside menus for accepting last adjustment
      Serial.println("'Z' pressed, no menu function assigned");
      break;
    case 'c': // Not assigned, C button held
      //    Serial.println("'C' Held");
      break;
    case 'z': // Not assigned, C button held
      Serial.print("'Z' Held");
      break;
    default:
      break;
    }
  }
}


