//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// I2C_lcd.cpp 
//
// Date:      2016/12/19
// By:        Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if (ARDUINO <  100)
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

#if (ARDUINO < 10000)
  #include <../Wire/Wire.h>
#else
  #include <Wire.h>
#endif
#include <inttypes.h>
#include "enumcodes.h"
#include "I2C_lcd.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Set includes for the LCD device
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef LCD_I2C_SAINSMART_YWROBOT || LCD_I2C_SAINSMART_YWROBOT_A
  #include <LCD.h>
  #include <LiquidCrystal_I2C.h>  
#endif // LCD_I2C_SAINSMART_YWROBOT || LCD_I2C_SAINSMART_YWROBOT_A

#ifdef LCD_I2C_PANELOLU2
  #include <../LiquidTWI2/LiquidTWI2.h>

#endif // LCD_I2C_PANELOLU2



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Set setting for the LCD device
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------
//// SETTINGS FOR LCD_I2C_SAINSMART_YWROBOTA 
//// fitted with a PCF8574A I2C device on 0x3f
//-----------------------------------------------------------------------
  #ifdef LCD_I2C_SAINSMART_YWROBOT
    #define I2C_ADDR    0x27      // I2C Address for LCD_I2C_TYPE_PCF8574
    #define LCD_WIDTH   20
    #define LCD_HEIGHT  4
  #endif // LCD_I2C_SAINSMART_YWROBOT
//-----------------------------------------------------------------------
//// SETTINGS FOR LCD_I2C_SAINSMART_YWROBOT_A 
//// fitted with a PCF8574A I2C device on 0x3f
//-----------------------------------------------------------------------
  #ifdef LCD_I2C_SAINSMART_YWROBOT_A
    #define I2C_ADDR    0x3f      // I2C Address for LCD_I2C_TYPE_PCF8574_A
    #define LCD_WIDTH   20
    #define LCD_HEIGHT  4
  #endif // LCD_I2C_SAINSMART_YWROBOT_A
//-----------------------------------------------------------------------
//// SETTINGS FOR LCD_I2C_PANELOLU2 
//// fitted with a LCD_I2C_TYPE_MCP23017 I2C device on 0x20
//-----------------------------------------------------------------------
  #ifdef LCD_I2C_PANELOLU2
    #define I2C_ADDR    0x20      // I2C Address for LCD_I2C_TYPE_MCP23017
    #define LCD_WIDTH   20
    #define LCD_HEIGHT  4
  #endif // LCD_I2C_PANELOLU2








//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// defines
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
void Init_LCD();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// extenal variables
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float current_position[] ;              // hook to X,Y,Z and E positions
extern int fanSpeeds[] ;                       // hook to fan speed 0 = off, 255 = full on
extern int feedrate;                           // hook to feedrate
extern int tt ;                                // hook to Extruder temperature in C
extern int bt ;                                // hook to Heated Bed temperature in C
extern int ett ;                               // hook to Extruder target temperature in C
extern int btt ;                               // hook to Heated Bed target temperature in C
extern int status ;                            // hook to printer status
extern int error_code ;                        // hook to error status 0=Nothing, 1=Heater thermistor error, 2= bed
extern const char* pszStatusString[];          // hook status strings
extern const char* pszErrorCodeString[] ;      // hook to error strings
extern const char* pszFirmware[] ;             // hook to Firmware strings

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// local variables and classes
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef LCD_I2C_SAINSMART_YWROBOT || LCD_I2C_SAINSMART_YWROBOT_A
  LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
#endif // LCD_I2C_SAINSMART_YWROBOT || LCD_I2C_SAINSMART_YWROBOTA

#ifdef LCD_I2C_PANELOLU2
 // Connect via i2c, default address #0 (A0-A2 not jumpered)
  LiquidTWI2 lcd(0x20,0,0);      
#endif // LCD_I2C_PANELOLU2


long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

char  szTemp[41];                              // temp work aria for sprintf
char  szT[41] ;                                // workspace for float to string conversions
bool  bNewStatusScreen = true;
float faOldPosition[NUM_AXIS] = { -1, -1, -1, 0.0};
int   iPrinterState = STATE_IDLE;		   	   // printer state
const char* pszPrinterState[] = { "Idle    ",
                                  "Heating ",
                                  "Printing",
                                  "Done    " };



byte byDegree[8] = {      B01100,
                          B10010,
                          B10010,
                          B01100,
                          B00000,
                          B00000,
                          B00000,
                          B00000 };

byte byThermometer[8] = { B00100,
                          B01010,
                          B01010,
                          B01010,
                          B01010,
                          B10001,
                          B10001,
                          B01110 };
                                
byte byBedTemp[8] = {     B00000,
                          B11111,
                          B10101,
                          B10001,
                          B10101,
                          B11111,
                          B00000,
                          B00000 };

byte byFanLeft[8] = {     B11111,
                          B10011,
                          B11001,
                          B11100,
                          B11100,
                          B11001,
                          B10011,
                          B11111 };

byte byFanRight[8] = {    B11111,
                          B11001,
                          B10001,
                          B00111,
                          B00111,
                          B10001,
                          B11001,
                          B11111 };                          

byte byFeedRate[8] = {    B11100,
                          B10000,
                          B11000,
                          B10111,
                          B00101,
                          B00110,
                          B00101,
                          B00000 };

byte byClock[8] = {       B00000,
                          B01110,
                          B10011,
                          B10101,
                          B10001,
                          B01110,
                          B00000,
                          B00000  };
                          
byte byCorner[4][8] = { { B00000,
                          B00000,
                          B00000,
                          B00000,
                          B00001,
                          B00010,
                          B00100,
                          B00100
                        },{
                          B00000,
                          B00000,
                          B00000,
                          B11100,
                          B11100,
                          B01100,
                          B00100,
                          B00100
                       }, {
                          B00100,
                          B00010,
                          B00001,
                          B00000,
                          B00000,
                          B00000,
                          B00000,
                          B00000
                       }, {
                          B00100,
                          B01000,
                          B10000,
                          B00000,
                          B00000,
                          B00000,
                          B00000,
                          B00000
                       } };
                          
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
#ifdef LCD_DISPLAY_FAN
    lcd.setCursor( 0, 2 ); 
    sprintf( szTemp, "%c%c%d%c", LCD_FAN_L_CHAR, LCD_FAN_R_CHAR, ((fanSpeeds[0]*100)/255), 37 );
    lcd.print( szTemp );
#else
    lcd.setCursor( 0, 2 ); 
    long lFeedPercentage = constrain(( (long)feedrate * (long)100)/ (long)2964, 0, 100);
    sprintf( szTemp, "%c%3ld%c ", LCD_FEEDRATE_CHAR, lFeedPercentage, 37 );
    lcd.print( szTemp );
#endif // LCD_DISPLAY_FAN

  // do the elapsed time clock
  lcd.setCursor( 14, 2 );
  long timeNow = millis();
  int iDays = timeNow / day ;                                //number of days
  int iHours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
  int iMinutes = ((timeNow % day) % hour) / minute ;         //and so on...
  int iSeconds = (((timeNow % day) % hour) % minute) / second;
  sprintf( szTemp, "%c%02d:%02d", LCD_CLOCK_CHAR, iHours, iMinutes);
  lcd.print( szTemp );

  // do fourth line
  PrinterState( );
  lcd.setCursor(0,3);
  if( status == STATUS_ERROR ){
    if(error_code){
      sprintf( szTemp, "Error: %s          ", pszErrorCodeString[error_code] );
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

  char szDashes[] = "-------------------------------------";
  int iLen = max(strlen(pszFirmware[FIRMWARE_NAME]), strlen(pszFirmware[FIRMWARE_MACHINENAME])) + 2 ;
  szDashes[iLen] = 0;
  
  Init_LCD();
  for (byte i = 1; i < 5; i++)
    lcd.createChar(i, byCorner[i-1]);

  sprintf( szTemp, "%c%s%c", 1, szDashes, 2 );
  lcd.setCursor((LCD_WIDTH/2)-(strlen(szTemp)/2) ,0); 
  lcd.print( szTemp );
  sprintf( szTemp,  "| %s |", pszFirmware[FIRMWARE_NAME]) ;
  lcd.setCursor((LCD_WIDTH/2)-(strlen(szTemp)/2) ,1); 
  lcd.print( szTemp );
  sprintf( szTemp,  "| %s |", pszFirmware[FIRMWARE_MACHINENAME]) ;
  lcd.setCursor((LCD_WIDTH/2)-(strlen(szTemp)/2) ,2); 
  lcd.print( szTemp );
  sprintf( szTemp, "%c%s%c", 3, szDashes, 4);
  lcd.setCursor((LCD_WIDTH/2)-(strlen(szTemp)/2) ,3); 
  lcd.print( szTemp );
  delay(4000);
  
  lcd.createChar(LCD_DEGREE_CHAR,byDegree);
  lcd.createChar(LCD_THERMOMETER,byThermometer); 
  lcd.createChar(LCD_BEDTEMP_CHAR,byBedTemp);
  lcd.createChar(LCD_FAN_L_CHAR,byFanLeft);
  lcd.createChar(LCD_FAN_R_CHAR,byFanRight);
  lcd.createChar(LCD_CLOCK_CHAR,byClock);
  lcd.createChar(LCD_FEEDRATE_CHAR,byFeedRate);

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
  sprintf( szTemp, "%c%3d/%d%c     ", LCD_THERMOMETER, tt, ett, LCD_DEGREE_CHAR );
  *(szTemp+10) = 0;               // truncate to 10 letters
  lcd.print( szTemp );
  // heated bed
  lcd.setCursor( 10, 0 ); 
  sprintf( szTemp, "%c%3d/%d%c     ", LCD_BEDTEMP_CHAR, bt, btt, LCD_DEGREE_CHAR );
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

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// void Init_LCD()
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void Init_LCD() {
  
#ifdef LCD_I2C_SAINSMART_YWROBOT || LCD_I2C_SAINSMART_YWROBOT_AA
  lcd.begin (LCD_WIDTH, LCD_HEIGHT);                  // initialize the lcd
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);
  lcd.clear();
  lcd.home();
#endif  // #ifdef LCD_I2C_SAINSMART_YWROBOT || LCD_I2C_SAINSMART_YWROBOTA

#ifdef LCD_I2C_PANELOLU2
  lcd.setMCPType(LTI_TYPE_MCP23017);
  // set up the LCD's number of rows and columns:
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  lcd.setBacklight(LED_ON);
  lcd.clear();
  lcd.home();
#endif // #ifdef LCD_I2C_PANELOLU2


}
