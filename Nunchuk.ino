Navchuk nunchuk = Navchuk();

void initializeNavchuk(void)
{
  nunchuk.init();
  Serial.println("Nunchuk interface initialized");
}

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

void waitForCbutton(void)
{
  do
  {
    nunchuk.update();
  } while(nunchuk.userInput !='C' && nunchuk.userInput !='Z');
  ms.next();
}  

