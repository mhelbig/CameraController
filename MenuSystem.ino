/////////////////////////////////////////////////////////////////////////////////
// General menu functions and behavior
/////////////////////////////////////////////////////////////////////////////////
void navigationHandler() 
{
  nunchuk.update();
//  if(nunchuk.userInput != ' ') Serial.println(nunchuk.userInput);
  
// dim the display when nobody's using the nunchuk, turn it on when they are
   if(nunchuk.userInput != ' ')
       lcd.setBacklight(true);
   if(nunchuk.userInput == 'I')
       lcd.setBacklight(false);

  if(ms.menu_item_is_selected())  // jump right into the active menu
  {
    ms.select(0);
  }
  else                             // if no menu active, let the user choose one
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
    case 'E': // error condition
      displayError("Nunchuk not detected");
      while(1);  //Freeze here forever until we find a way to hot restart the Nunchuk device
    case 'C': // Not assigned - used inside menus for cancelling last adjustment
      break;
    case 'Z': // Not assigned - used inside menus for accepting last adjustment
      break;
    case 'c': // Not assigned, C button held, used inside some menus
      break;
    case 'z': // Not assigned, Z button held, used inside some menus
      break;
    default:
      break;
    }
  }
}


