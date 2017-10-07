//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// V3.cpp - Contains the Eaglemoss V3 specific declarations
//
// By Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "SerialManager.h"
#include "V3.h"
#include "Configuration.h"
#include "pins.h"
#include "sprinter.h"
#include <stdio.h>
#include <Wire.h>
#include <EEPROM.h>
#include "V3_EEPROM.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// variables unique to the V3 3D printer
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char PauseID = 0x03;                  //rp3d.com pause id
char HSW_Enable = 0x01;               //rp3d.com M237, M238
char MuteBeeps = 0x0;                 // 
int FSW_Counter = 0;                  //rp3d.com Front Switch Counter
int FSW_status = 1;                   //rp3d.com Front Switch Status

float fPauseSavedZ;                   // variable to save Z poistion in

unsigned long S_to_take = axis_steps_per_unit[2]*10;  //number of steps required to move Z 10mm
unsigned long S_count = 0;            // Steps taken counter
unsigned long previous_millis_PauseID;

int Fil_out=0;                        //Filament status
int Z_estop=20;

#define PAUSE_STEP_DELAY 10

union data {
  float v;
  unsigned char fchar[4];
} fvalue; 

extern float destination[] ;
extern float current_position[];


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Move Z Axis Down 10mm
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define PAUSE_PLAY
#define PAUSE_BILL

inline void Z_DN()
{
  SerialMgr.cur()->println("Filament Run Out");

#ifdef PAUSE_PLAY

  fPauseSavedZ = current_position[Z_AXIS];
  destination[Z_AXIS] = fPauseSavedZ + 10 ;
  prepare_move();
  
#else
  
  #ifdef PAUSE_BILL

  pinMode(26,OUTPUT); //Z enable
  pinMode(3,OUTPUT);  //Z Step
  pinMode(2,OUTPUT);  //Z Dir
  
  digitalWrite(2,HIGH); // set direction
  digitalWrite(26,LOW); // Enable Z axis
 
  while((digitalRead(Z_estop)==HIGH)&&(S_count < S_to_take)){ // check Z enstop before moving
    digitalWrite(3,HIGH);
    delayMicroseconds (7);
    digitalWrite(3,LOW);
    delayMicroseconds (7);
    S_count++;
  }
  
  #else  // pause suusi V1
  
  pinMode(Z_ENABLE_PIN,OUTPUT);      //Z enable  
  pinMode(Z_STEP_PIN,OUTPUT);        //Z Step
  pinMode(Z_DIR_PIN,OUTPUT);         //Z Dir
  
  WRITE(Z_DIR_PIN,HIGH);             // set Z direction
  enable_z();                        // Enable Z axis
  while((READ(Z_MAX_PIN)==HIGH)&&(S_count < S_to_take))
  { 
    // check Z enstop before moving
    WRITE(Z_STEP_PIN, HIGH);
    delayMicroseconds (PAUSE_STEP_DELAY);
    WRITE(Z_STEP_PIN, LOW);
    delayMicroseconds (PAUSE_STEP_DELAY);
    S_count++;
  }
  
  #endif  //  PAUSE_BILL

#endif

}  

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Move Z axis UP 10mm
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void Z_UP()
{
  
#ifdef   PAUSE_PLAY
  
  destination[Z_AXIS] = fPauseSavedZ;
  prepare_move();
  Fil_out=0;
  
#else
  
  #ifdef PAUSE_BILL
  
  digitalWrite(26,LOW); // Enable Z axis
  digitalWrite(2,LOW);   // set Z direction
  
  while (S_count > 0){        
    digitalWrite(3,HIGH);
    delayMicroseconds (10);
    digitalWrite(3,LOW);
    delayMicroseconds (10);
    S_count--;
  }
  digitalWrite(26,HIGH);   // disable Z axis
  Fil_out=0;
  
  #else  // pause suusi V1
  
  WRITE(Z_DIR_PIN,LOW);          // set Z direction
  enable_z();                    // Enable Z axis
  while (S_count > 0)
  {        
    WRITE(Z_STEP_PIN, HIGH);
    delayMicroseconds (PAUSE_STEP_DELAY);
    WRITE(Z_STEP_PIN, LOW);
    delayMicroseconds (PAUSE_STEP_DELAY);
    S_count--;
  }
  disable_z();                    // disable Z axis
  Fil_out=0;

  #endif  //  PAUSE_BILL

#endif  //  PAUSE_PLAY

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void V3_I2C_Command ( int iCommand, boolean bEchoCommand )
//
// 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void V3_I2C_Command ( int iCommand, boolean bEchoCommand ) {
  char szChar[10];                            // workspace for echo string
  Wire.beginTransmission( V3_I2C_DEVICE );    // open comms with V3 I2C device
  Wire.send(iCommand);                        // Send command
  Wire.endTransmission();                     // end transmission
  if( bEchoCommand ) {
    sprintf( szChar, "M%d OK", iCommand );    // create echo string
    SerialMgr.cur()->println(szChar);         // echo result to serial manager
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// float Read_Z_MAX_LENGTH_M240_FromEEPROM() - reads and returns Z_MAX_LENGTH_M240 from the EEPROM
//
// unique to the V3 3D printer
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float Read_Z_MAX_LENGTH_M240_FromEEPROM() {
  for(int i = 0; i < 4; i++) {
    fvalue.fchar[i] = EEPROM.read(i + Z_MAX_LENGTH_EEPROM);
  }
  Serial.print("PrinterHeight: ");
  Serial.println(fvalue.v);
//  Z_MAX_LENGTH_M240 = fvalue.v;
  return fvalue.v;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void Write_Z_MAX_LENGTH_M240_ToEEPROM(float fZ_Max_Length) - reads Z_MAX_LENGTH_M240 from the EEPROM
//
// unique to the V3 3D printer
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Write_Z_MAX_LENGTH_M240_ToEEPROM(float fZ_Max_Length) {
  fvalue.v = fZ_Max_Length ;
  unsigned char *fpointer;
  fpointer = fvalue.fchar;
  for(int i = 0; i < 4; i++) {
    EEPROM.write(i + Z_MAX_LENGTH_EEPROM,*fpointer);
    fpointer++;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//       // setting for the 2016 firmware release
//
// unique to V3
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check_PauseID()
{
  
  if((millis() - previous_millis_PauseID) < 100 )                 //check the PauseID every 100mS
  {
    return;                                                       // return if less than 100 mS has elapsed
  }
  previous_millis_PauseID = millis();                             // update previous with current millis()
                                                                  // 100 mS has elapsed since the last button check

  V3_I2C_Command( V3_HOODSWITCH_ENABLE, false ) ;                 // Hood Switch Enable
//  SerialMgr.cur()->println("M237 OK");
                                                                  //char b = b011 ;
  Wire.requestFrom(0x48, 1);                                      // request 1 bytes from slave device #0x48

  while(Wire.available())
  {
    // slave may send less than requested
    char c = Wire.receive();                                      // receive a byte as character
//    SerialMgr.cur()->println(c, HEX);                             // print the character
//    PauseID = c & 0x03;                                           // mask off unwanted bits
    PauseID = c & V3_SWITCHES_MASK;                               // mask off unwanted bits
    SerialMgr.cur()->println(Fil_out, DEC);                             // print the character
 }

  if (HSW_Enable == HOODSWITCH_DISABLED)
  {
    // if hood switch is disabled
//    PauseID = PauseID | 0x01;                                     // then set it in software
    PauseID = PauseID | HOODSWITCH_BIT;                           // then set it in software
   }

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// this bit bit commented out by eaglemoss / reprap pro coder 
// thank the stars imagine 3 mins of beeping! >:) so I enabled it :D
//

  if( (HSW_Enable == HOODSWITCH_ENABLED) && ((PauseID & HOODSWITCH_BIT) == HOODSWITCH_OPEN) )
  { 
    V3_I2C_Command( V3_NOZZLE_RED_FLASH, false ) ;                // nozzel red flashing
    V3_I2C_Command( V3_BUTTON_RED_FLASH, false ) ;                // front red flashing
    V3_I2C_Command( V3_BEEP_FOR_3_MIN, false ) ;                  // Beep every sec, 3 min.
    FSW_status=-2;                                                // Enter Pause state
    Fil_out = 1;
    Z_DN();                                                       // Move Z down
  }  // end of if ( (HSW_Enable == 0x01) && ((PauseID & 0x01) == 0x00) )
	  
  if( (HSW_Enable == HOODSWITCH_ENABLED) && ((PauseID & HOODSWITCH_BIT) == HOODSWITCH_CLOSED) )
  {
    V3_I2C_Command( V3_BUTTON_BLUE, false ) ;                     // front blue
    V3_I2C_Command( V3_BEEP_OFF, false ) ;                        // beep off
    V3_I2C_Command( V3_NOZZLE_WHITE, false ) ;                    // nozzle white
    Fil_out=0;
  }  // end of if ( (HSW_Enable == 0x01) && ((PauseID & 0x01) == 0x01) )
/*
              */

// Front Button Switch		
// Long Press: “Emergency Stop” to Main Chip.
// Short Press:”Pause” to Main chip.
    
  if( FSW_Counter > FSW_COUNTER_MAX)
  {
    // FSW_Counter = 31; 
    EmergencyStop();                                              // forever stop 
  }  // end of if (FSW_Counter > 30)
  
  if( (FSW_Counter > FSW_COUNTER_MIN) && ( FSW_Counter <= FSW_COUNTER_MAX ) )
  {
    V3_I2C_Command( V3_SHORT_BEEP, false ) ;                      // beep short x1
    if( (PauseID & FRONT_BUTTON_BIT) == FRONT_BUTTON_RELEASED )
    {
      // Front Button Switch Released
//      PauseID = ~PauseID;
      if (Fil_out==0)
      {
        Z_UP();   // Move Z up
      }
      SerialMgr.cur()->println("Pause/Unpause");
      FSW_status = ~FSW_status;
      FSW_Counter = 0;                                            // reset press time counter
    }    // end of if ( (PauseID & 0x02) == 0x02 )
  }    // end of if( (FSW_Counter > 5) && ( FSW_Counter <= 30 ) )
 
  //else PauseID = 0x03;
 
  if( FSW_Counter <= FSW_COUNTER_MIN)
  {
    if( (PauseID & FRONT_BUTTON_BIT) == FRONT_BUTTON_RELEASED )
    {
      // Front Switch released  
      FSW_Counter = 0;                                            // Reset front button counter
    }    // end of if ( (PauseID & 0x02) == 0x02 )
  }    // end of if( FSW_Counter <= 5)
  
  if( (PauseID & FRONT_BUTTON_BIT) == FRONT_BUTTON_PRESSED )
  {
    // Front Switch pressed 
    FSW_Counter++;                                                // increment the button pressed time counter
//    PauseID = 0x03;
  }    // end of if ( (PauseID & 0x02) == 0 )
  
}
