#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Uncomment ONE of the next three lines - the one for your RepRap machine
#define V3

//-----------------------------------------------------------------------
//// The number of Extruders. Uncomment the one that describes your 3D printer
//-----------------------------------------------------------------------
#define _EXTRUDERS "1"
//#define _EXTRUDERS "2"

//-----------------------------------------------------------------------
//// Nozzel offset from X=0 Y=0 on the build plate
//-----------------------------------------------------------------------
// change to 0 if you do not need a offset 20160329
#define X_OFFSET 8
#define Y_OFFSET 12

//-----------------------------------------------------------------------
//// BASIC SETTINGS: select your board type, thermistor type, axis scaling, and endstop configuration
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
//// The following define selects which electronics board you have. Please choose the one that matches your setup
// MEGA/RAMPS up to 1.2  = 3,
// RAMPS 1.3 = 33
// Gen6 = 5,
// Sanguinololu up to 1.1 = 6
// Sanguinololu 1.2 and above, and Melzi = 62
//-----------------------------------------------------------------------
#define MOTHERBOARD 62

//-----------------------------------------------------------------------
//// Thermistor settings:
// 1 is 100k thermistor
// 2 is 200k thermistor
// 3 is mendel-parts thermistor
// 4 is 10k thermistor
//-----------------------------------------------------------------------
#define THERMISTORHEATER 1
#define THERMISTORBED 1

//-----------------------------------------------------------------------
//// SETTINGS FOR Stepper driver type
//-----------------------------------------------------------------------
// Un-Comment if you are using DRV8825 Stepper drivers for X and Y axis 
// the default is commented out for an un-modified V3 printer only use this
// setting if you have Bill Green's Stepper Mod fitted with DRV8825 steppers
// drivers in the X and Y Axis.
#define STEPPER_DRIVER_X_Y_DRV8825      

//-----------------------------------------------------------------------
//// Calibration variables
//-----------------------------------------------------------------------
// X, Y, Z, E steps per unit - Metric Prusa Mendel with Wade extruder:
//  #define _AXIS_STEP_PER_UNIT {91.4286, 91.4286, 4000, 910};
//  #define _AXIS_STEP_PER_UNIT {80.00,     80.00, 2560, 910};

//// Calibration variables
// X, Y, Z, E steps per unit - V3 
//  #define _AXIS_STEP_PER_UNIT {78.82, 78.82,78.82,99.6150};   //V3-Z-belt fitted with A4988 stepper drivers for X, Y, Z and E 
//  #define _AXIS_STEP_PER_UNIT {78.82, 78.82,400,99.6150};     //V3-Z-screw fitted with A4988 stepper drivers for X, Y, Z and E 

#ifndef STEPPER_DRIVER_X_Y_DRV8825
  #define _AXIS_STEP_PER_UNIT {78.82, 78.82, 2560, 99.6150}     //V3-Z-screw2 fitted with A4988 stepper drivers for X, Y, Z and E (the default for the V3 )
#else  // else of #ifndef STEPPER_DRIVER_X_Y_DRV8825
  #define _AXIS_STEP_PER_UNIT {157.64, 157.64, 2560, 99.6150}   //V3-Z-screw2 with X and Y fitted with DRV8825 stepper drivers and A4988 stepper drivers for Z and E
#endif  //  #ifndef STEPPER_DRIVER_X_Y_DRV8825

//-----------------------------------------------------------------------
//// Endstop Settings
//-----------------------------------------------------------------------
//#define ENDSTOPPULLUPS 1 // Comment this out (using // at the start of the line) to disable the endstop pullup resistors
// The pullups are needed if you directly connect a mechanical endswitch between the signal and ground pins.
  const bool ENDSTOPS_INVERTING = true; //set to true to invert the logic of the endstops
//If your axes are only moving in one direction, make sure the endstops are connected properly.
//If your axes move in one direction ONLY when the endstops are triggered, set ENDSTOPS_INVERTING to true here

//-----------------------------------------------------------------------
// This determines the communication speed of the printer
//-----------------------------------------------------------------------
#define BAUDRATE 115200

//-----------------------------------------------------------------------
// Comment out (using // at the start of the line) to disable SD support:
//-----------------------------------------------------------------------
#define SDSUPPORT 1

//-----------------------------------------------------------------------
// Uncomment to make run init.g from SD on boot
//-----------------------------------------------------------------------
#define SDINITFILE

//-----------------------------------------------------------------------
// Comment out (using // at the start of the line) to disable Bluetooth support:
//-----------------------------------------------------------------------
//#define BLUETOOTH
#ifdef BLUETOOTH
	#define BLUETOOTH_SERIAL Serial1
#endif

//-----------------------------------------------------------------------
// catch all for the V3 
//-----------------------------------------------------------------------
#ifndef V3
  #error Uncomment #define V3 at the start of the file Configuration.h
#endif

//-----------------------------------------------------------------------
//// ADVANCED SETTINGS - to tweak parameters
//-----------------------------------------------------------------------

//#include "thermistortables.h"

// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0
#define E_ENABLE_ON 0

// Disables axis when it's not being used.
const bool DISABLE_X = false;
const bool DISABLE_Y = false;
const bool DISABLE_Z = false;
const bool DISABLE_E = false;

// Inverting axis direction
const bool INVERT_X_DIR = false;
const bool INVERT_Y_DIR = false;
const bool INVERT_Z_DIR = false;
const bool INVERT_E_DIR = true;

//-----------------------------------------------------------------------
//// ENDSTOP SETTINGS:
// Sets direction of endstops when homing; 1=MAX, -1=MIN
//-----------------------------------------------------------------------
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR 1

  const bool min_software_endstops = false; //If true, axis won't move to coordinates less than zero.
  const bool max_software_endstops = true;  //If true, axis won't move to coordinates greater than the defined lengths below.


//-----------------------------------------------------------------------
//// Heated bed extent
//-----------------------------------------------------------------------
#ifdef V3
  const int X_MAX_LENGTH = 140;
  const int Y_MAX_LENGTH = 140;
  const int Z_MAX_LENGTH = 130;
#else
  const int X_MAX_LENGTH = 220;    
  const int Y_MAX_LENGTH = 220;
  const int Z_MAX_LENGTH = 240;
#endif


//-----------------------------------------------------------------------
//// MOVEMENT SETTINGS
//-----------------------------------------------------------------------
  const int NUM_AXIS = 4; // The axis order in all axis related arrays is X, Y, Z, E
  /*
//  float max_feedrate[] = {3000, 3000, 800, 10000}; //V3 Z-belt
  float max_feedrate[] = {3000, 3000, 350, 10000}; //V3 Z-screw
//  float homing_feedrate[] = {1500,1500,800}; //V3 Z-blet
  float homing_feedrate[] = {1500,1500,350}; //V3 Z-screw
  bool axis_relative_modes[] = {false, false, false, false};    */
  
  //#define _MAX_FEEDRATE {3000, 3000, 800, 10000};       //V3 Z-belt   (mm/sec)
  #define _MAX_FEEDRATE {3000, 3000, 350, 10000}        //V3 Z-screw   (mm/sec)
  //#define _HOMING_FEEDRATE  {1500,1500,800};            //V3 Z-belt   (mm/min) !!
  #define _HOMING_FEEDRATE  {1500,1500,350};            //V3 Z-screw   (mm/min) !!
  #define _AXIS_RELATIVE_MODES {false, false, false, false}
  

// Min step delay in microseconds. If you are experiencing missing steps, try to raise the delay microseconds, but be aware this
// If you enable this, make sure STEP_DELAY_RATIO is disabled.
//#define STEP_DELAY_MICROS 1

// Step delay over interval ratio. If you are still experiencing missing steps, try to uncomment the following line, but be aware this
// If you enable this, make sure STEP_DELAY_MICROS is disabled. (except for Gen6: both need to be enabled.)
//#define STEP_DELAY_RATIO 0.25

//-----------------------------------------------------------------------
//// Ramp Accelertaion settings
//-----------------------------------------------------------------------
// Comment this to disable ramp acceleration
#define RAMP_ACCELERATION 1

// Acceleration settings
#ifdef RAMP_ACCELERATION
  #define _MAX_START_SPEED_UNITS_PER_SECOND {25.0,25.0,25.0,10.0}              // X, Y, Z, E maximum start speed for accelerated moves. E default values are good for skeinforge 40+, for older versions raise them a lot.
//  #define _MAX_ACCELERATION_UNITS_PER_SQ_SECOND {1000,1000,1000,250}           // X, Y, Z and E max acceleration in mm/s^2 for printing moves or retracts. V3 Z-belt
  #define _MAX_ACCELERATION_UNITS_PER_SQ_SECOND {1000,1000,50,250}            // X, Y, Z and E max acceleration in mm/s^2 for printing moves or retracts. V3 Z-screw
//  #define _MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND {500,500,500,500};      // X, Y, Z max acceleration in mm/s^2 for travel moves. V3 Z-belt
  #define _MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND {500,500,50,500}        // X, Y, Z max acceleration in mm/s^2 for travel moves. V3 Z-screw
#endif

//-----------------------------------------------------------------------
// Machine UUID
//-----------------------------------------------------------------------
// This may be useful if you have multiple machines and wish to identify them by using the M115 command.
// By default we set it to zeros.
#define _DEF_CHAR_UUID "00000000-0000-0000-0000-000000000000"
// 

//-----------------------------------------------------------------------
//// AD595 THERMOCOUPLE SUPPORT UNTESTED... USE WITH CAUTION!!!!
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//// PID settings:
//-----------------------------------------------------------------------
// Uncomment the following line to enable PID support. This is untested and could be disastrous. Be careful.
#define PIDTEMP 1
#ifdef PIDTEMP
  #define _PID_MAX 255       // limits current to nozzle
  #define _PID_I_MAX 80      //130;//125;
  #define _PID_KP 2         //1.10;
  #define _PID_KI 0.01 
  #define _PID_KD 20.0      //0.01;
#endif

//-----------------------------------------------------------------------
//// SETTINGS FOR Z PROBE FUNCTION (Command G29 and G30)
//-----------------------------------------------------------------------

// Comment out (using // at the start of the line) to disable Bed Probe support:
#define HAS_BED_PROBE 1

#ifdef HAS_BED_PROBE
  #define Z_INCREMENT 0.05                  // increments for probing Z Height
  #define Z_NEGETIVE_TRIGGER 1              // Z probe: 1 if a Negetive Pulse, 0 if a Positive Pulse on trigger
  #define X_PROBE_OFFSET_FROM_EXTRUDER -45  // X offset: -left  +right  [of the nozzle] (Must Be an Integer)
  #define Y_PROBE_OFFSET_FROM_EXTRUDER -10  // Y offset: -front +behind [the nozzle] (Must Be an Integer)
  #define Z_PROBE_OFFSET_FROM_EXTRUDER 0    // Z offset: -below +above  [the nozzle] (Can be a Float)

  #define Z_CLEARANCE_BETWEEN_PROBES   5    // Z Clearance between probe points

#endif

//-----------------------------------------------------------------------
//// SETTINGS FOR M42  - Switch I/O pin (Command M42)
//-----------------------------------------------------------------------
// comment out of no M42 support
#define M42_SUPPORT

//-----------------------------------------------------------------------
//// SETTINGS FOR EXPERIMENTAL_I2CBUS pinched from Marlin 1.1.0
//
// M260 - Send data to a I2C slave device 
// M261 - Request X bytes from I2C slave device 
//-----------------------------------------------------------------------
// comment out if no EXPERIMENTAL_I2CBUS
#define EXPERIMENTAL_I2CBUS

//-----------------------------------------------------------------------
//// SETTINGS FOR M355  - Case light on or off (Command M355)
//-----------------------------------------------------------------------
// comment out if no M355 support 
#define M355_SUPPORT


//-----------------------------------------------------------------------
//// SETTINGS FOR M499  - Force Error mode(Command M499)
//-----------------------------------------------------------------------
// comment out if no M499 support (only used to test BBB() error reporting)
//#define M499_SUPPORT

//-----------------------------------------------------------------------
//// STORE SETTINGS TO EEPROM
//-----------------------------------------------------------------------
// the microcontroller can store settings in the EEPROM
// M500 - stores paramters in EEPROM
// M501 - reads parameters from EEPROM (if you need reset them after you changed them temporarily).
// M502 - reverts to the default "factory settings". You still need to store them in EEPROM afterwards if you want to.
// M503 - Print settings
// define this to enable eeprom support
#define USE_EEPROM_SETTINGS

// to disable EEPROM Serial responses and decrease program space by ~1000 byte: comment this out:
// please keep turned on if you can.
#define PRINT_EEPROM_SETTING

//-----------------------------------------------------------------------
//// Setting for the software control of fans
// a V3 has two fans extruder and work fan. Only the work fan is software controlable
//-----------------------------------------------------------------------
#define FAN_COUNT 2

//-----------------------------------------------------------------------
//// M109 target window - machine will deem to have reached target temperature when nozzle reaches Temp = target - NZONE.
//-----------------------------------------------------------------------
//  #define NZONE = 5;//2;      // setting for the 2016 and 2017 Eaglemoss firmware releases
  #define _NZONE 2         // setting for the V1.01 firmware release


//-----------------------------------------------------------------------
//// Sets the Initial speed of the work cooling fan
//-----------------------------------------------------------------------
#define FAN_INIT 200

//-----------------------------------------------------------------------
//// How often should the heater check for new temp readings, in milliseconds
//-----------------------------------------------------------------------
#define HEATER_CHECK_INTERVAL 112
#define BED_CHECK_INTERVAL 5000

//-----------------------------------------------------------------------
// Comment the following line to enable heat management during acceleration
//-----------------------------------------------------------------------
//#define DISABLE_CHECK_DURING_ACC

#ifndef DISABLE_CHECK_DURING_ACC
  // Uncomment the following line to disable heat management during moves
  //#define DISABLE_CHECK_DURING_MOVE
#endif

//-----------------------------------------------------------------------
//// Heater Management
//  Uncomment the following line to disable heat management during travel moves
//  (and extruder-only moves, eg: retracts), strongly recommended if you are
//  missing steps mid print.
//  Probably this should remain commented if are using PID.
//  It also defines the max milliseconds interval after which a travel move is
//  not considered so for the sake of this feature.
//-----------------------------------------------------------------------
//#define DISABLE_CHECK_DURING_TRAVEL 1000

//-----------------------------------------------------------------------
//// Temperature smoothing - only uncomment this if your temp readings are noisy (Gen6 without EvdZ's 5V hack)
//-----------------------------------------------------------------------
//#define SMOOTHING 1
//#define SMOOTHFACTOR 16 //best to use a power of two here - determines how many values are averaged together by the smoothing algorithm

//-----------------------------------------------------------------------
//// Experimental watchdog and minimal temp
// The watchdog waits for the watchperiod in milliseconds whenever an M104 or M109 increases the target temperature
// If the temperature has not increased at the end of that period, the target temperature is set to zero. It can be reset with another M104/M109
//-----------------------------------------------------------------------
//#define WATCHPERIOD 5000 //5 seconds

//-----------------------------------------------------------------------
//// The minimal temperature defines the temperature below which the heater will not be enabled
//-----------------------------------------------------------------------
#define MINTEMP 5

//-----------------------------------------------------------------------
//// Experimental max temp
// When temperature exceeds max temp, your heater will be switched off.
// This feature exists to protect your hotend from overheating accidentally, but *NOT* from thermistor short/failure!
// You should use MINTEMP for thermistor short/failure protection.
//-----------------------------------------------------------------------
#define MAXTEMP 270
#define MAXTEMPBED 130

// Select one of these only to define how the nozzle temp is read.
#define HEATER_USES_THERMISTOR
//#define HEATER_USES_AD595
//#define HEATER_USES_MAX6675

// Select one of these only to define how the bed temp is read.
#define BED_USES_THERMISTOR
//#define BED_USES_AD595

//-----------------------------------------------------------------------
//// Debug Settings
//-----------------------------------------------------------------------
// Uncomment the following line to enable debugging. You can better control debugging below the following line
//#define DEBUG
#ifdef DEBUG
  //#define DEBUG_PREPARE_MOVE //Enable this to debug prepare_move() function
  //#define DEBUG_BRESENHAM //Enable this to debug the Bresenham algorithm
  //#define DEBUG_RAMP_ACCELERATION //Enable this to debug all constant acceleration info
  //#define DEBUG_MOVE_TIME //Enable this to time each move and print the result
  //#define DEBUG_HEAT_MGMT //Enable this to debug heat management. WARNING, this will cause axes to jitter!
  //#define DEBUG_DISABLE_CHECK_DURING_TRAVEL //Debug the namesake feature, see above in this file
#endif

//-----------------------------------------------------------------------
////Debug setting for debugging PID
//-----------------------------------------------------------------------
//#define DEBUG_PID



/****************************************************************************************
* Sanguinololu pin assignment
*
****************************************************************************************/
#if MOTHERBOARD == 62
#define MOTHERBOARD 6
#define SANGUINOLOLU_V_1_2
#endif
#if MOTHERBOARD == 6
#define KNOWN_BOARD 1
#ifndef __AVR_ATmega644P__
#ifndef __AVR_ATmega1284P__
#error Oops!  Make sure you have the appropriate 'Sanguino' selected from the 'Tools -> Boards' menu.
#endif
#endif

//x axis pins

#define X_STEP_PIN         15
#define X_DIR_PIN          21
#define X_MIN_PIN          18
#define X_MAX_PIN           -2

//y axis pins

#define Y_STEP_PIN         22
#define Y_DIR_PIN          23
#define Y_MIN_PIN          19
#define Y_MAX_PIN          -1

//z axis pins

#define Z_STEP_PIN         3
#define Z_DIR_PIN          2
#define Z_MIN_PIN          -1
#define Z_MAX_PIN          20

//extruder pins

#define E_STEP_PIN         1
#define E_DIR_PIN          0


#define CASE_LIGHT_PIN     30     // Case light pin (A1) 
//#define PROBE_PIN          29     // Melzi1284p (A2)
#define PROBE_PIN          11     // Z height probe (TX1) on V3
#define TOOL_PIN           28     // Tool select pin 
#define LED_PIN            27     // LED pin (A4)

#define FAN_PIN            4

#define PS_ON_PIN          -1
#define KILL_PIN           -1

#define HEATER_0_PIN       13 // (extruder)

#ifdef SANGUINOLOLU_V_1_2

#define HEATER_1_PIN       12 // (bed)
#define X_ENABLE_PIN       14
#define Y_ENABLE_PIN       14
#define Z_ENABLE_PIN       26
#define E_ENABLE_PIN       14

#else

#define HEATER_1_PIN       14  // (bed)
#define X_ENABLE_PIN       -1
#define Y_ENABLE_PIN       -1
#define Z_ENABLE_PIN       -1
#define E_ENABLE_PIN       -1

#endif

#define TEMP_0_PIN          7   // MUST USE ANALOG INPUT NUMBERING NOT DIGITAL OUTPUT NUMBERING!!!!!!!!! (pin 33 extruder)
#define TEMP_1_PIN          6   // MUST USE ANALOG INPUT NUMBERING NOT DIGITAL OUTPUT NUMBERING!!!!!!!!! (pin 34 bed)
#define SDPOWER          -1
#define SDSS          31

#ifndef KNOWN_BOARD
#error Unknown MOTHERBOARD value in configuration.h
#endif

#endif
#endif
