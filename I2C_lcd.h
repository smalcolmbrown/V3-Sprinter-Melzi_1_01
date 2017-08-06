//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// I2C_lcd.h 
//
// Date:      2016/12/19
// By:        Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef I2C_LCD_H
  #define I2C_LCD_H
  
  // include the config detailes for the LCD
  #include "Config_LCD.h"

// custom charecter defines
  #define LCD_DEGREE_CHAR 1
  #define LCD_THERMOMETER 2
  #define LCD_BEDTEMP_CHAR 3
  #define LCD_FAN_L_CHAR 4
  #define LCD_FAN_R_CHAR 5
  #define LCD_CLOCK_CHAR 6
  #define LCD_FEEDRATE_CHAR 7

// LCD connection defines
  #define BACKLIGHT_PIN  3
  #define En_pin  2
  #define Rw_pin  1
  #define Rs_pin  0
  #define D4_pin  4
  #define D5_pin  5
  #define D6_pin  6
  #define D7_pin  7

// LCD backlight defines
  #define  LED_OFF  0
  #define  LED_ON  1


  void SplashScreen();
  void StatusScreen();
  void DisplayAxisPosition( int iAxis );
  void DisplayBedAndExtruderTemparature();
#endif
