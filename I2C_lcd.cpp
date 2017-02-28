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
// defines
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define NUM_AXIS 4
#define NUM_DIGITS 7
#define NUM_PRECISION 1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// local function declarations
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertleadingSpacesToZeros( char* source );
void PrinterState();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// extenal variables
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
extern const char* pszFirmware[] ;             // hook to Firmware strings
extern const char* uuid ;                      // hook to error UUID string

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// local variables and classes
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char  szTemp[41];                              // temp work aria for sprintf
char  szT[41] ;                                // workspace for float to string conversions
bool  bNewStatusScreen = true;
float faOldPosition[NUM_AXIS] = { -1, -1, -1, 0.0};
int   iPrinterState = STATE_IDLE;		   	   // printer state
const char* pszPrinterState[] = { "Idle    ",
                                  "Heating ",
                                  "Printing",
                                  "Done    " };

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void PrinterState()
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void PrinterState( ){
	switch( iPrinterState){
		case STATE_IDLE:
			// If the bed or extruder temperature is set to anything other than
			// zero then we are heating: change state, otherwise do nothing.
			if ( ett || btt) {
				iPrinterState = STATE_HEATING;
			}
			break;
		case STATE_HEATING:
			// If the extruder temperature is within 5 degrees of the extruder target
			// temperature then change state, otherwise do nothing. The bed temperature
			// does not matter as some do not use a heated bed.
			if( tt >= (ett -5) && (ett != 0 )){
				iPrinterState = STATE_PRINTING;
			}
			break;
		case STATE_PRINTING:
			// We are printing if the target temperature drops to Zero then we have 
			// finished the job change state otherwise do nothing.
			if ( !ett ) {
				iPrinterState = STATE_DONE;
			}
			break;
		case STATE_DONE:
			// we have finished the job nothing left to do.
			break;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void StatusScreen()
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void StatusScreen(){
  
  if( bNewStatusScreen ) {
    lcd.clear();
    lcd.home();
    bNewStatusScreen=false;
  }
                                                     // do first line
  DisplayBedAndExtruderTemparature();                // display Extruder and heated bed temparture
                                                     // do second line
  DisplayAxisPosition( 0 );                          // X Axis position
  DisplayAxisPosition( 1 );                          // Y Axis position
  DisplayAxisPosition( 2 );                          // Axis Y position

  // do third line
  
  lcd.setCursor( 0, 2 ); 
  sprintf( szTemp, "Fan %s", (bFanOn)? "On " : "Off" );
  lcd.print( szTemp );

  // do fourth line
  PrinterState( );
  lcd.setCursor(0,3);
  if( status == STATUS_ERROR ){
    if(error_code){
      sprintf( szTemp, "Error: %s          ", error_code_str[error_code] );
      lcd.print( szTemp );
    }
  } else {
    // no error
    sprintf( szTemp, "%s: %s", pszFirmware[FIRMWARE_MACHINENAME], pszPrinterState[iPrinterState]);
//    sprintf( szTemp, "%s: %s", pszFirmware[FIRMWARE_NAME], status_str[status]);
    lcd.print( szTemp );
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void SplashScreen()
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void SplashScreen() {
  int i ;
  lcd.begin (20,4);  // initialize the lcd
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);
  lcd.clear();
  lcd.home();
  lcd.setCursor(10-(strlen(pszFirmware[FIRMWARE_MACHINENAME])/2) ,0); 
  lcd.print( pszFirmware[FIRMWARE_MACHINENAME] );
  sprintf(szTemp, "V %s Dev", pszFirmware[FIRMWARE_VERSION] );
  lcd.setCursor(10-(strlen(szTemp)/2),1);
  lcd.print(szTemp);
  lcd.setCursor(0,2);
  strncpy( szTemp, uuid, 20) ;
  lcd.print( szTemp );
  lcd.setCursor(0,3);
  strncpy( szTemp, uuid+20, 20) ;
  lcd.print( szTemp );
  delay(4000);
  bNewStatusScreen = true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DisplayBedAndExtruderTemparature()
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayBedAndExtruderTemparature() {
  // extruder 
  lcd.setCursor( 0, 0 ); 
  sprintf( szTemp, "%c%d/%d%c     ", 0x5c, tt, ett, 0xdf );
  *(szTemp+10) = 0;               // truncate to 10 letters
  lcd.print( szTemp );
  // heated bed
  lcd.setCursor( 10, 0 ); 
  sprintf( szTemp, "%c%d/%d%c     ", 0xfc, bt, btt, 0xdf );
  *(szTemp+10) = 0;               // truncate to 10 letters
  lcd.print( szTemp );
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void DisplayAxisPosition( int iAxis )
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayAxisPosition( int iAxis ) {
  if( faOldPosition[iAxis] != current_position[iAxis] ) {
    lcd.setCursor( 7*iAxis, 1 );
    ConvertleadingSpacesToZeros( dtostrf( current_position[iAxis], NUM_DIGITS, NUM_PRECISION, szT) );
    sprintf( szTemp, "%c%s", 'X'+iAxis, szT+2 );
    lcd.print( szTemp );
    faOldPosition[iAxis] = current_position[iAxis] ;
  }
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

