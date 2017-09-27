//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// V3_EEPROM.h
//
// Date:      2016/12/19
// By:        Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef V3_EEPROM.h
  #define V3_EEPROM.h
  
// EEPROM related variables
#define Z_ADJUST_BYTE            0                                       // byte 0-255 (0-2.55 mm)                    1 byte
#define Z_MAX_LENGTH_EEPROM      (Z_ADJUST_BYTE+ sizeof(byte))           // float Z height                            4 bytes
#define HOOD_SWITCH_EEPROM       (Z_MAX_LENGTH_EEPROM + sizeof(float))   // byte hood switch default                  1 byte
#define MUTE_BEEP_EEPROM         (HOOD_SWITCH_EEPROM+ sizeof(byte))      // mute unessential beeps                    1 byte



#define EEPROM_OFFSET 100

// IMPORTANT:  Whenever there are changes made to the variables stored in EEPROM
// in the functions below, also increment the version number. This makes sure that
// the default values are used whenever there is a change to the data, to prevent
// wrong data being written to the variables.
// ALSO:  always make sure the variables in the Store and retrieve sections are in the same order.
#define EEPROM_VERSION "S00"


extern float axis_steps_per_unit[4]; 
extern float max_feedrate[4];
extern long  max_acceleration_units_per_sq_second[4];
extern long  max_travel_acceleration_units_per_sq_second[4];
extern int   nzone;

#define EEPROM_AXIS_STEPS_PER_UNIT                              (EEPROM_OFFSET + 4*sizeof(char))
#define EEPROM_MAX_FEEDRATE                                     (EEPROM_AXIS_STEPS_PER_UNIT + 4*sizeof(float))
#define EEPROM_MAX_ACCELERATION_UNITS_PRER_SQ_SECOND            (EEPROM_MAX_FEEDRATE + 4*sizeof(float))
#define EEPROM_MAX_TRAVEL_ACCELERATION_UNITS_PRER_SQ_SECOND     (EEPROM_MAX_ACCELERATION_UNITS_PRER_SQ_SECOND + 4*sizeof(long))
#define EEPROM_KP                                               (EEPROM_MAX_TRAVEL_ACCELERATION_UNITS_PRER_SQ_SECOND + 4*sizeof(long))
#define EEPROM_KI                                               (EEPROM_KP + sizeof(float))
#define EEPROM_KD                                               (EEPROM_KI + sizeof(float))
#define EEPROM_PID_MAX                                          (EEPROM_KD + sizeof(float))
#define EEPROM_PID_I_MAX                                        (EEPROM_PID_MAX + sizeof(int))
#define EEPROM_NZONE                                            (EEPROM_PID_I_MAX + sizeof(int))

extern void EEPROM_RetrieveSettings(bool def, bool printout );
extern void EEPROM_printSettings();
extern void EEPROM_StoreSettings();
  
#endif  
