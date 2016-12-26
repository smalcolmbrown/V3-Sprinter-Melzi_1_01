//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// I2C_lcd.cpp 
//
// Date:      2016/12/19
// By:        Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "enumcodes.h"
#include "I2C_lcd.h"
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library
// download the repository from here and put it in your documents/arduino/libraries folder and restart your ide 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// adaptations needed to work with arduino version 0023
/*
LiquidCrystal_I2C_ByVac.h

change from 
#include <Arduino.h>
to
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// local declarations
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertleadingSpacesToZeros( char* source );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// local variables
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define ERROR_CODE_NO_ERROR 0
//#define ERROR_CODE_HOTEND_TEMPERATURE 1
//#define ERROR_CODE_BED_TEMPERATURE 2

//#define STATUS_OK 0
//#define STATUS_SD 1
//#define STATUS_ERROR 2


#define NUM_AXIS 4
#define NUM_DIGITS 7
#define NUM_PRECISION 1
extern float current_position[] ;              // hook to X,Y,Z and E positions
extern bool bFanOn ;                           // hook to fan status false = off true = on
extern int tt ;                                // hook to Extruder temperature in C
extern int bt ;                                // hook to Heated Bed temperature in C
extern int ett ;                               // hook to Extruder target temperature in C
extern int btt ;                               // hook to Heated Bed target temperature in C
extern int status ;                            // hook to printer status
extern int error_code ;                        // hook to error status 0=Nothing, 1=Heater thermistor error, 2= bed
extern const char* status_str[] ;              // hook status strings
extern const char* error_code_str[] ;          // hook to error strings

char  szTemp[41];                              // temp work aria for sprintf
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void StatusScreen()
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void StatusScreen(){
  char szT[40] ;    // workspace
  lcd.clear();
  lcd.home();
  
  // do first line 
  
  // extruder 
  lcd.setCursor( 0, 0 ); 
  sprintf( szTemp, "%c%d/%d%c", 0x5c, tt, ett, 0xdf );
  lcd.print( szTemp );
  // heated bed
  lcd.setCursor( 10, 0 ); 
  sprintf( szTemp, "%c%d/%d%c", 0xfc, bt, btt, 0xdf );
  lcd.print( szTemp );

  // do second line
  
  lcd.setCursor( 0, 1 );
  ConvertleadingSpacesToZeros( dtostrf( current_position[0], NUM_DIGITS, NUM_PRECISION, szT) );
  sprintf( szTemp, "X%s", szT+2 );
  lcd.print( szTemp );
  
  lcd.setCursor(7,1);
  ConvertleadingSpacesToZeros( dtostrf( current_position[1], NUM_DIGITS, NUM_PRECISION, szT) );
  sprintf( szTemp, "Y%s", szT+2 );
  lcd.print(szTemp);
  
  lcd.setCursor(14,1);
  ConvertleadingSpacesToZeros( dtostrf( current_position[2], NUM_DIGITS, NUM_PRECISION, szT) );
  sprintf( szTemp, "Z%s", szT+2 );
  lcd.print(szTemp);

  // do third line
  
  lcd.setCursor( 0, 2 ); 
  sprintf( szTemp, "Fan %s", (bFanOn)? "On" : "Off" );
  lcd.print( szTemp );

  // do fourth line
  
  lcd.setCursor(0,3);
  if( status == STATUS_ERROR ){
    if(error_code){
      sprintf( szTemp, "Error: %s", error_code_str[error_code] );
      lcd.print( szTemp );
    }
  } else {
    // no error
    sprintf( szTemp, "Sprinter: %s", status_str[status]);
    lcd.print( szTemp );
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void SplashScreen()
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void SplashScreen() {
  lcd.begin (20,4);  // initialize the lcd
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);
  lcd.clear();
  lcd.home();
  lcd.setCursor(0,0); 
  lcd.print("Vector 3 3D Printer");
  lcd.setCursor(3,1);
  lcd.print("Version  V1.01");
  lcd.setCursor(6,3);
  lcd.print("Sprinter");
  delay(4000);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void ConvertleadingSpacesToZeros( char* source )
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertleadingSpacesToZeros( char* source ) {
  while(*source++ ) {
    if (isWhitespace(*source)) {
      *source = '0';
    }
  }
}


