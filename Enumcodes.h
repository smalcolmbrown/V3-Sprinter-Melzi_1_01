//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Enumcodes.h
//
// Date:      2016/12/19
// By:        Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ENUMCODES_H
  #define ENUMCODES_H
  
enum StatusCodes { 
    STATUS_OK = 0, 
    STATUS_SD, 
    STATUS_ERROR,
    STATUS_FINISHED,
    STATUS_PAUSE,
    STATUS_ABORT 
  };

  enum ErrorCodes { 
    ERROR_CODE_NO_ERROR = 0, 
    ERROR_CODE_HOTEND_TEMPERATURE, 
    ERROR_CODE_BED_TEMPERATURE 
  };

  enum Firmware {
    FIRMWARE_NAME = 0,
    FIRMWARE_URL,
    FIRMWARE_VERSION,
    FIRMWARE_MACHINENAME,
    FIRMWARE_EXTRUDERS
  };
  
#endif
