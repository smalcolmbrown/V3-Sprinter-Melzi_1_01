//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// V3.cpp
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <WProgram.h>
#include "V3.h"
#include <stdio.h>
#include <Wire.h>
#include "SerialManager.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// variables unique to the V3 3D printer
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char PauseID = 0x03;                  //rp3d.com pause id
char HSW_Enable = 0x01;               //rp3d.com M237, M238

int FSW_Counter = 0;                  //rp3d.com Front Switch Counter
int FSW_status = 1;                   //rp3d.com Front Switch Status

unsigned long previous_millis_PauseID;

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
    SerialMgr.cur()->println("M233 OK");      // echo result to serial manager
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void check_PauseID()
//
// 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check_PauseID() {
  
  if((millis() - previous_millis_PauseID) < 100 ) {               //check the PauseID every 100mS
    
    return;                                                       // return if less than 100 mS has elapsed
    
  }
  // 100 mS has elapsed since the last button check
  previous_millis_PauseID = millis();                             // update previous with current millis()
  
  V3_I2C_Command( V3_HOODSWITCH_ENABLE, false ) ;                 // Hood Switch Enable
//  SerialMgr.cur()->println("M237 OK");
  //char b = 0x03;
  Wire.requestFrom(0x48, 1);                                      // request 1 bytes from slave device #0x48

  while(Wire.available()) {
    // slave may send less than requested
    char c = Wire.receive();                                      // receive a byte as character
//    SerialMgr.cur()->println(c, HEX);                           // print the character
    PauseID = c & 0x03;                                           // mask off unwanted bits
  }

  if (HSW_Enable == 0x00){                                        // if hood switch is disabled
    
    PauseID = PauseID | 0x01;                                     // then set it in software
    
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// this bit bit commented out by eaglemoss coder thank the stars 
// imagine 3 mins of beeping!
//

/*
  if ( (HSW_Enable == 0x01) && ((PauseID & 0x01) == 0x00) ){      // M212, M223, M235; front red flashing, nozzle red flashing, Beep every sec, 3 min.
  
    V3_I2C_Command( V3_NOZZLE_RED_FLASH, false ) ;                // nozzel red flashing
    V3_I2C_Command( V3_BUTTON_RED_FLASH, false ) ;                // front red flashing
    V3_I2C_Command( V3_BEEP_FOR_3_MIN, false ) ;                  // Beep every sec, 3 min.
    
  }
  
  if ( (HSW_Enable == 0x01) && ((PauseID & 0x01) == 0x01) ){      // M226, M236, M217; front blue, beep off, nozzle white
    
    V3_I2C_Command( V3_BUTTON_BLUE, false ) ;                     // front blue
    V3_I2C_Command( V3_BEEP_OFF, false ) ;                        // beep off
    V3_I2C_Command( V3_NOZZLE_WHITE, false ) ;                    // nozzle white
    
 }
              */

// Front Switch		
// Long Press: “Emergency Stop” to Main Chip.
// Short Press:”Pause” to Main chip.
                                                                  // Long Press: “Emergency Stop” to Main Chip.
                    
  if (FSW_Counter > 30){                                          // FSW_Counter = 31; 
    
    EmergencyStop();                                              // forever stop 

  }    // end of if (FSW_Counter > 30)
                            
// Short Press:”Pause” to Main chip.
                                                                  // Short Press: ”Pause” to Main chip.                            
  
  if( (FSW_Counter > 5) && ( FSW_Counter <= 30 ) ) {
    
    V3_I2C_Command( V3_SHORT_BEEP, false ) ;                      // beep short x1
                              
    if ( (PauseID & 0x02) == 0x02 ) {                             // released the Front Switch
      
//      PauseID = ~PauseID;
      SerialMgr.cur()->println("Pause/Unpause");
      
      FSW_status = ~FSW_status;
      FSW_Counter = 0;   
    }    // end of if ( (PauseID & 0x02) == 0x02 )

  }    // end of if( (FSW_Counter > 5) && ( FSW_Counter <= 30 ) )

  //else PauseID = 0x03;
                            
  if( FSW_Counter <= 5){
    if ( (PauseID & 0x02) == 0x02 ){                              // released the Front Switch
      FSW_Counter = 0;
    }    // end of if ( (PauseID & 0x02) == 0x02 )
  }    // end of if( FSW_Counter <= 5)
  
  // if the front button is pressed increment the button pressed time counter
  
  if ( (PauseID & 0x02) == 0 ){
    
    FSW_Counter++;
    
//    PauseID = 0x03;
    
  }    // end of if ( (PauseID & 0x02) == 0 )
  
}
