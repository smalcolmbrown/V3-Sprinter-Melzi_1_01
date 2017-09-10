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
  
  
#endif  
