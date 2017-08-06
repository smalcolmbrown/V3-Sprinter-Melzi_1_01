//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Config_LCD.h 
//
// Date:      2017/08/06
// By:        Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_LCD_H
  #define CONFIG_LCD_H

//-----------------------------------------------------------------------
//// SETTINGS FOR Malsoft I2C LCD 
//// Comment out the I2C device NOT used
//-----------------------------------------------------------------------
#define PCF8574
//  #define PCF8574A

//-----------------------------------------------------------------------
//// SETTINGS FOR Malsoft I2C LCD 
//// PCF8574 I2C device
//// Comment out the I2C addresses NOT used
//-----------------------------------------------------------------------
  #ifdef PCF8574
//    #define I2C_ADDR    0x20  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x21  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x22  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x23  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x24  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x25  // Define I2C Address for PCF8574 port expander
//    #define I2C_ADDR    0x26  // Define I2C Address for PCF8574 port expander
    #define I2C_ADDR    0x27  // Define I2C Address for PCF8574 port expander (default)
  #endif // PCF8574
//-----------------------------------------------------------------------
//// SETTINGS FOR Malsoft I2C LCD 
//// PCF8574A I2C device
//// Comment out the I2C addresses NOT used
//-----------------------------------------------------------------------
  #ifdef PCF8574A
//    #define I2C_ADDR    0x38  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x39  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3a  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3b  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3c  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3d  // Define I2C Address for PCF8574A port expander
//    #define I2C_ADDR    0x3e  // Define I2C Address for PCF8574A port expander
    #define I2C_ADDR    0x3f  // Define I2C Address for PCF8574A port expander (default)
  #endif // PCF8574A

//-----------------------------------------------------------------------
//// SETTINGS FOR Malsoft I2C LCD 
//// LCD height and width which must be defined
//-----------------------------------------------------------------------

  #define LCD_WIDTH 20
  #define LCD_HEIGHT 4

//-----------------------------------------------------------------------
//// SETTINGS FOR Malsoft I2C LCD 
//// Comment out if you want to display the feed rate percentage
//// if LCD_DISPLAY_FAN is #defined the fan percentage is displayed
//-----------------------------------------------------------------------
//  #define LCD_DISPLAY_FAN

//-----------------------------------------------------------------------
//// SETTINGS FOR Malsoft I2C LCD 
//// comment out if you do not want elapsed print time displayed
//-----------------------------------------------------------------------
  #define LCD_CLOCK

#endif
