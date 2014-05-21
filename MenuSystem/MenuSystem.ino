/*
  LCDAdvancedNav.ino - Example code using the menu system library
 and a lcd 16x2 display (controled over serial).
 
 Created by Niesteszeck, Dec 8th 2013.
 Released into the public domain.
 
 License: GPL 3
 */

#include <MenuSystem.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Navchuk.h>

#define I2C_ADDR    0x3F
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

// Menu variables
MenuSystem ms;
Menu mm("Camera Controller");
Menu tlMenu("Timelapse Mode");
MenuItem tl_framesPerSecond("Set # frames/sec");
MenuItem tl_shootTime("Set shoot time");
MenuItem tl_motionProfile("Set motion profile");
Menu pmMenu("Panograph Mode");
MenuItem pm_autoMode("Panograph Auto");

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin,BACKLIGHT_PIN,POSITIVE);

// initialize the nunchuk interface
Navchuk nunchuk = Navchuk();

// Menu callback function
// In this example all menu items use the same callback.

void on_item1_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Frames/sec = 30");
  waitForCbutton();
}

void on_item2_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Shoot time = 1 hr");
  waitForCbutton();
}

void on_item3_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Motion = SPLINE");
  waitForCbutton();
}

void on_item4_selected(MenuItem* p_menu_item)
{
  lcd.setCursor(0,1);
  lcd.print("Pano Mode = AUTO");
  waitForCbutton();
}

void waitForCbutton(void)
{
  do
  {
    nunchuk.update();
  } while(nunchuk.userInput !='C' && nunchuk.userInput !='Z');
}  

// Standard arduino functions

void setup() {
  Serial.begin(9600);
  nunchuk.init();
  lcd.begin(20,4);               // initialize the lcd 
  Serial.println("Setting up the menu.");

  // Menu setup
  mm.add_menu(&tlMenu);
  tlMenu.add_item(&tl_framesPerSecond, &on_item1_selected);
  tlMenu.add_item(&tl_shootTime, &on_item2_selected);
  tlMenu.add_item(&tl_motionProfile, &on_item3_selected);
  mm.add_menu(&pmMenu);
  pmMenu.add_item(&pm_autoMode, &on_item4_selected);
  ms.set_root_menu(&mm);
  Serial.println("Menu set up.");
  displayMenu();
}

void loop() 
{
  navigationHandler();
}

void displayMenu()
{
  lcd.clear();
  lcd.setCursor(0,0);
  // Display the menu
  Menu const* cp_menu = ms.get_current_menu();

  //lcd.print("Current menu name: ");
  lcd.print(cp_menu->get_name());
  
  lcd.setCursor(0,1);
  
  lcd.print(cp_menu->get_selected()->get_name());
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

