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
//// Select LCD Type 
//-----------------------------------------------------------------------
// comment out LCD displays that are not fitted.
#define LCD_I2C_SAINSMART_YWROBOT    1      // using PCF8574 0x27
//#define LCD_I2C_SAINSMART_YWROBOT_A  1      // using PCF8574A 0x3f
//#define LCD_I2C_PANELOLU2            1      // using MCP23017 0x20
//-----------------------------------------------------------------------
//// Comment out if you want to display the feed rate percentage
//// if LCD_DISPLAY_FAN is #defined the fan percentage is displayed
//-----------------------------------------------------------------------
//  #define LCD_DISPLAY_FAN


#ifdef LCD_I2C_SAINSMART_YWROBOT || LCD_I2C_SAINSMART_YWROBOT_A || LCD_I2C_PANELOLU2
  #define LCD_SUPPORTED
#endif

#endif  // CONFIG_LCD_H
