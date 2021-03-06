//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// V3_EEPROM.cpp
//
// Date:      2017/09/14
// By:        Pinched from Kliment Sprinter Mods by Suusi M-B
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "Configuration.h"
#include "V3_EEPROM.h"
#include "Sprinter.h"
#include "SerialManager.h"

#ifdef PIDTEMP

  extern float Kp;
  extern float Ki;
  extern float Kd;
  extern int   pid_max;
  extern int   pid_i_max;
  
#endif

//#ifdef USE_EEPROM_SETTINGS


//======================================================================================
//========================= Read / Write EEPROM =======================================
template <class T> int EEPROM_write_setting(int address, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  int i;
  for (i = 0; i < (int)sizeof(value); i++)
    eeprom_write_byte((unsigned char *)address++, *p++);
  return i;
}

template <class T> int EEPROM_read_setting(int address, T& value)
{
  byte* p = (byte*)(void*)&value;
  int i;
  for (i = 0; i < (int)sizeof(value); i++)
    *p++ = eeprom_read_byte((unsigned char *)address++);
  return i;
}
//======================================================================================


void EEPROM_StoreSettings() 
{
  char ver[4]= "000";
  EEPROM_write_setting(EEPROM_OFFSET, ver); // invalidate data first
  EEPROM_write_setting(EEPROM_AXIS_STEPS_PER_UNIT, axis_steps_per_unit);
  EEPROM_write_setting(EEPROM_MAX_FEEDRATE, max_feedrate);
  EEPROM_write_setting(EEPROM_MAX_ACCELERATION_UNITS_PRER_SQ_SECOND, max_acceleration_units_per_sq_second);
  EEPROM_write_setting(EEPROM_MAX_TRAVEL_ACCELERATION_UNITS_PRER_SQ_SECOND, max_travel_acceleration_units_per_sq_second);

  //PID Settings
  
#ifdef PIDTEMP
  EEPROM_write_setting(EEPROM_KP, Kp);     //Kp
  EEPROM_write_setting(EEPROM_KI, Ki);     //Ki
  EEPROM_write_setting(EEPROM_KD, Kd);     //Kd
  EEPROM_write_setting(EEPROM_PID_MAX, pid_max);
  EEPROM_write_setting(EEPROM_PID_I_MAX, pid_i_max);
  EEPROM_write_setting(EEPROM_NZONE, nzone);
#else
  // store default settings for non PID builds
  EEPROM_write_setting(EEPROM_KP, _KP_TERM);     //Kp
  EEPROM_write_setting(EEPROM_KI, _KI_TERM);     //Ki
  EEPROM_write_setting(EEPROM_KD, _KD_TERM);     //Kd
  EEPROM_write_setting(EEPROM_PID_MAX, _PID_MAX);
  EEPROM_write_setting(EEPROM_PID_I_MAX, _PID_I_MAX);
  EEPROM_write_setting(EEPROM_NZONE, _NZONE);
#endif
  

  char ver2[4]=EEPROM_VERSION;
  EEPROM_write_setting(EEPROM_OFFSET, ver2); // validate data
  SerialMgr.cur()->println("Settings Stored");
 
}


void EEPROM_printSettings()
{  
  #ifdef PRINT_EEPROM_SETTING
      SerialMgr.cur()->println("Steps per unit:");
      SerialMgr.cur()->print(" M92 X");
      SerialMgr.cur()->print(axis_steps_per_unit[0]);
      SerialMgr.cur()->print(" Y");
      SerialMgr.cur()->print(axis_steps_per_unit[1]);
      SerialMgr.cur()->print(" Z");
      SerialMgr.cur()->print(axis_steps_per_unit[2]);
      SerialMgr.cur()->print(" E");
      SerialMgr.cur()->println(axis_steps_per_unit[3]);
      
      SerialMgr.cur()->println("Maximum Acceleration (mm/s2):");
      SerialMgr.cur()->print("  M201 X");
      SerialMgr.cur()->print(max_acceleration_units_per_sq_second[0] ); 
      SerialMgr.cur()->print(" Y");
      SerialMgr.cur()->print(max_acceleration_units_per_sq_second[1] ); 
      SerialMgr.cur()->print(" Z");
      SerialMgr.cur()->print(max_acceleration_units_per_sq_second[2] );
      SerialMgr.cur()->print(" E");
      SerialMgr.cur()->println(max_acceleration_units_per_sq_second[3]);

      SerialMgr.cur()->println("Maximum Travel Acceleration (mm/s2):");
      SerialMgr.cur()->print("  M202 X");
      SerialMgr.cur()->print(max_travel_acceleration_units_per_sq_second[0] ); 
      SerialMgr.cur()->print(" Y");
      SerialMgr.cur()->print(max_travel_acceleration_units_per_sq_second[1] ); 
      SerialMgr.cur()->print(" Z");
      SerialMgr.cur()->print(max_travel_acceleration_units_per_sq_second[2] );
      SerialMgr.cur()->print(" E");
      SerialMgr.cur()->println(max_travel_acceleration_units_per_sq_second[3]);

      SerialMgr.cur()->println("Maximum feedrates (mm/s):");
      SerialMgr.cur()->print("  M203 X");
      SerialMgr.cur()->print(max_feedrate[0]);
      SerialMgr.cur()->print(" Y");
      SerialMgr.cur()->print(max_feedrate[1]); 
      SerialMgr.cur()->print(" Z");
      SerialMgr.cur()->print(max_feedrate[2]); 
      SerialMgr.cur()->print(" E");
      SerialMgr.cur()->println(max_feedrate[3]);

    #ifdef PIDTEMP
    
      SerialMgr.cur()->println("PID settings:");
      SerialMgr.cur()->print("  M301 P");
      SerialMgr.cur()->print(Kp); 
      SerialMgr.cur()->print(" I");
      SerialMgr.cur()->print(Ki); 
      SerialMgr.cur()->print(" D");
      SerialMgr.cur()->print(Kd);
      SerialMgr.cur()->print(" PID_Max");
      SerialMgr.cur()->print(pid_max);
      SerialMgr.cur()->print(" PID_I Max");
      SerialMgr.cur()->print(pid_i_max);
      SerialMgr.cur()->print(" NZONE");
      SerialMgr.cur()->println(nzone);
    
    #endif
  #endif

} 


void EEPROM_RetrieveSettings(bool def, bool printout)
{  // if def=true, the default values will be used

  int i=EEPROM_OFFSET;
  char stored_ver[4];
  char ver[4]=EEPROM_VERSION;
    
  EEPROM_read_setting(EEPROM_OFFSET,stored_ver); //read stored version
  if ((!def)&&(strncmp(ver,stored_ver,3)==0))
  {
    // version number match
    EEPROM_read_setting(EEPROM_AXIS_STEPS_PER_UNIT, axis_steps_per_unit);
    EEPROM_read_setting(EEPROM_MAX_FEEDRATE, max_feedrate);
    EEPROM_read_setting(EEPROM_MAX_ACCELERATION_UNITS_PRER_SQ_SECOND, max_acceleration_units_per_sq_second);
    EEPROM_read_setting(EEPROM_MAX_TRAVEL_ACCELERATION_UNITS_PRER_SQ_SECOND, max_travel_acceleration_units_per_sq_second);

#ifdef PIDTEMP
    EEPROM_read_setting(EEPROM_KP, Kp);
    EEPROM_read_setting(EEPROM_KI, Ki);
    EEPROM_read_setting(EEPROM_KD, Kd);
    EEPROM_read_setting(EEPROM_PID_MAX, pid_max);
    EEPROM_read_setting(EEPROM_PID_I_MAX, pid_i_max);
    EEPROM_read_setting(EEPROM_NZONE, nzone);
       
#endif

    SerialMgr.cur()->println("Stored settings retreived");
  }
  else 
  {

  const float tmp1[] = _AXIS_STEP_PER_UNIT;
  const float tmp2[] = _MAX_FEEDRATE;
  const long  tmp3[] = _MAX_ACCELERATION_UNITS_PER_SQ_SECOND;
  const long  tmp4[] = _MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND;
  for (short i=0;i<4;i++) 
  {
    axis_steps_per_unit[i]                         =tmp1[i];  
    max_feedrate[i]                                =tmp2[i];  
    max_acceleration_units_per_sq_second[i]        =tmp3[i];
    max_travel_acceleration_units_per_sq_second[i] =tmp4[i];
  }
      
#ifdef PIDTEMP
  Kp        = _PID_KP;
  Ki        = _PID_KI;
  Kd        = _PID_KD;
  pid_max   = _PID_MAX;
  pid_i_max = _PID_I_MAX;
  nzone     = _NZONE;
#endif

  SerialMgr.cur()->println("Using Default settings");
  }
    
  if(printout)
  {
    EEPROM_printSettings();
  }
}  

//#endif
