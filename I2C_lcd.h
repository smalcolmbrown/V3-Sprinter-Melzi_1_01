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
  
  // comment out the option that is not used
  #define PCF8574
//  #define PCF8574A

  #ifdef PCF8574
//    #define I2C_ADDR    0x20  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x21  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x22  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x23  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x24  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x25  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x26  // Define I2C Address for PCF8574 port expander
    #define I2C_ADDR    0x27  // Define I2C Address for PCF8574 port expander
  #endif
  #ifdef PCF8574A
//    #define I2C_ADDR    0x38  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x39  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3a  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3b  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3c  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3d  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3e  // Define I2C Address for PCF8574A port expander
    #define I2C_ADDR    0x3f  // Define I2C Address for PCF8574A port expander
  #endif

// 
  #define LCD_WIDTH 20
  #define LCD_HEIGHT 4
  
// custom charecter defines
  #define LCD_DEGREE_CHAR 1
  #define LCD_THERMOMETER 2
  #define LCD_BEDTEMP_CHAR 3
  #define LCD_FAN_L_CHAR 4
  #define LCD_FAN_R_CHAR 5
  #define LCD_CLOCK_CHAR 6
  #define LCD_FEEDRATE_CHAR 7

  #define BACKLIGHT_PIN  3
  #define En_pin  2
  #define Rw_pin  1
  #define Rs_pin  0
  #define D4_pin  4
  #define D5_pin  5
  #define D6_pin  6
  #define D7_pin  7

  #define  LED_OFF  0
  #define  LED_ON  1


  void SplashScreen();
  void StatusScreen();
  void DisplayAxisPosition( int iAxis );
  void DisplayBedAndExtruderTemparature();
#endif
