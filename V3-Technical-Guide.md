# Eaglemoss Vector 3 Firmware Technical Guide

## Contents

### 1. Supported G amd M Codes
#### 1.a Supported G Codes
#### 1.b Supported M Codes
### 2. Main board pin out
#### 2.a Pin definition for the Vector 3
#### 2.b Pin assignments on the Vector 3


# Section 1 Supported G Codes.

## The following G Codes have been implemented

### G0  - Rapid linear Move 
Same as G1
### G1  - Linear Move
#### Usage
G0 Xnnn Ynnn Znnn Ennn Fnnn Snnn

G1 Xnnn Ynnn Znnn Ennn Fnnn Snnn
#### Parameters
Not all parameters need to be used, but at least one has to be used

Xnnn The position to move to on the X axis

Ynnn The position to move to on the Y axis

Znnn The position to move to on the Z axis

Ennn The amount to extrude between the starting point and ending point

Fnnn The feedrate per minute of the move between the starting point and ending point (if supplied)

#### Examples
G0 X12               ; move to 12mm on the X axis

G0 F1500             ; Set the feedrate to 1500mm/minute

G1 X90.6 Y13.8 E22.4 ; Move to 90.6mm on the X axis and 13.8mm on the Y axis while extruding 22.4mm of material

### G4  - Dwell S<seconds> or P<milliseconds>
#### Usage
Pause the machine for a period of time. P for milliseconds and S for seconds
#### Parameters
Pnnn Time to wait, in milliseconds

Snnn Time to wait, in seconds 
#### Example
G4 P200
### G28 -  Move to Origin (Home)
#### Parameters
This command can be used without any additional parameters.

X Flag to go back to the X axis origin

Y Flag to go back to the Y axis origin

Z Flag to go back to the Z axis origin
#### Examples
G28     ; Home all axes

G28 X Z ; Home the X and Z axes
### G30 - Single Z-Probe
####  Usage
G30 Pnnn Xnnn Ynnn Znnn Hnnn Snnn
#### Parameters
Pnnn Probe point number

Xnnn X coordinate

Ynnn Y coordinate

Znnn Z coordinate

Snnn Set parameter
#### Example
G30                          ; Probe the bed at the current XY position. When the probe is triggered, set the Z coordinate to the probe trigger height.

G30 S-1                      ; Probe the bed at the current XY position. When the probe is triggered, do not adjust the Z coordinate.

G30 X20 Y50                  ; Probe the bed at X20 Y50 and save the XY coordinates

G30 X180 Y180 S-1            ; As previous example but just report the height errors
### G90 - Use Absolute Coordinates
#### Example
G90                          ; All coordinates from now on are absolute relative to the origin of the machine.
### G91 - Use Relative Coordinates
#### Example
G91                          ; All coordinates from now on are relative to the last position. 
### G92 - Set current position to cordinates given
#### Parameters
This command can be used without any additional parameters.

Xnnn new X axis position

Ynnn new Y axis position

Znnn new Z axis position

Ennn new extruder position
#### Example
G92 X10 E90                  ; Allows programming of absolute zero point, by reseting the current position to the values specified. 
## RepRap and Custom M Codes

### M4   - Query Status.                       (V3 only)
#### Usage
Querries the Status
#### Parameters
None
#### Example
M4                           ; returns machien status and error code if set
#### Responce
S<int>,<Verbose Status>      ; if no error
   
S<int><Error>                ; if error
   
EC:<int><Verbose Error
### M5   - Reset Status and Clears Error flag. (V3 only)
#### Usage
Resets the status flag and clears error flag if set
#### Parameters
None
#### Example
M5                           ; Reset Status and Clears Error flag.
### M20  - List SD card
### M21  - Init SD card
### M22  - Release SD card
### M23  - Select SD file (M23 filename.g)
### M24  - Start/resume SD print
### M25  - Pause SD print
### M26  - Set SD position in bytes (M26 S12345)
### M27  - Report SD print status
### M28  - Start SD write (M28 filename.g)
### M29  - Stop SD write does not do anything.
### M42  - Switch I/O pin
### M80  - Turn on Power Supply
### M81  - Turn off Power Supply
### M82  - Set E codes absolute (default)
### M83  - Set E codes relative while in Absolute Coordinates (G90) mode
### M84  - Disable steppers until next move, or use S<seconds> to specify an inactivity timeout, after which the steppers will be disabled.  S0 to disable the timeout.
### M85  - Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
### M92  - Set axis_steps_per_unit - same syntax as G92
### M104 - Set extruder target temp
### M105 - Read current temp
### M106 - Fan on
### M107 - Fan off
### M109 - Wait for extruder current temp to reach target temp.
### M114 - Display current position
### M115 - Capabilities string
### M119 - Report endstops status.
### M140 - Set bed target temp
### M190 - Wait for bed current temp to reach target temp.
### M201 - Set max acceleration in units/s^2 for print moves (M201 X1000 Y1000)
### M202 - Set max acceleration in units/s^2 for travel moves (M202 X1000 Y1000)
### M203 - Adjust Z height
### M205 - Advanced settings
### M211 - sends 211 to V3_I2C device, extruder Red LED on
### M212 - sends 212 to V3_I2C device, extruder Red LED flashing
### M213 - sends 213 to V3_I2C device, extruder Green LED on
### M214 - sends 214 to V3_I2C device, extruder Green LED flashing
### M215 - sends 215 to V3_I2C device, extruder Blue LED on
### M216 - sends 216 to V3_I2C device, extruder Blue LED flashing
### M217 - sends 217 to V3_I2C device, extruder White LED on
### M218 - sends 218 to V3_I2C device, extruder White LED flashing
### M219 - sends 219 to V3_I2C device, extruder Orange LED on
### M220 - sends 220 to V3_I2C device, extruder Orange LED flashing
### M221 - sends 221 to V3_I2C device, extruder Head LED OFF
### M222 - sends 222 to V3_I2C device, front button LED Red
### M223 - sends 223 to V3_I2C device, front button LED Red Flashing
### M224 - sends 224 to V3_I2C device, front button LED Green
### M225 - sends 225 to V3_I2C device, front button LED Green flashing
### M226 - sends 226 to V3_I2C device, front button LED Blue
### M227 - sends 227 to V3_I2C device, front button LED Green flashing
### M228 - sends 228 to V3_I2C device, front button LED White
### M229 - sends 229 to V3_I2C device, front button LED White flashing
### M230 - sends 230 to V3_I2C device, front button front LED Orange
### M231 - sends 231 to V3_I2C device, front button front LED Orange flashing
### M232 - sends 232 to V3_I2C device, front button front LED OFF
### M233 - sends 233 to V3_I2C device, Short Beep x 3
### M234 - sends 234 to V3_I2C device, Long Beep x 1 ( 3 sec)
### M235 - sends 235 to V3_I2C device, Beep every sec, 3 min.
### M236 - sends 236 to V3_I2C device, Beep Off
### M237 - Hood Switch Enable
### M238 - Hood Switch Disable
### M239 - sends 239 to V3_I2C device, Short Beep
### M240 - set Z_MAX_LENGTH_M240
   ### M260 - 
   ### m261 - 
### M301 - set PID parameter

# Section 2 The pin asignments

## 2.a Pin definition for the Vector 3

   ATMEL ATMEGA644/ATMEGA1284 / SANGUINO
  
                          +---\/---+
              (D 0) PB0  1|        |40  PA0 (AI 0 / D31)
              (D 1) PB1  2|        |39  PA1 (AI 1 / D30)
         INT2 (D 2) PB2  3|        |38  PA2 (AI 2 / D29)
          PWM (D 3) PB3  4|        |37  PA3 (AI 3 / D28)
       SS PWM (D 4) PB4  5|        |36  PA4 (AI 4 / D27)
         MOSI (D 5) PB5  6|        |35  PA5 (AI 5 / D26)
         MISO (D 6) PB6  7|        |34  PA6 (AI 6 / D25)
          SCK (D 7) PB7  8|        |33  PA7 (AI 7 / D24)
                    RST  9|        |32  AREF
                    VCC 10|        |31  GND
                    GND 11|        |30  AVCC
                  XTAL2 12|        |29  PC7 (D 23)
                  XTAL1 13|        |28  PC6 (D 22)
         RX0 (D 8)  PD0 14|        |27  PC5 (D 21) TDI
         TX0 (D 9)  PD1 15|        |26  PC4 (D 20) TDO
    INT0 RX1 (D 10) PD2 16|        |25  PC3 (D 19) TMS
    INT1 TX1 (D 11) PD3 17|        |24  PC2 (D 18) TCK
         PWM (D 12) PD4 18|        |23  PC1 (D 17) SDA
         PWM (D 13) PD5 19|        |22  PC0 (D 16) SCL
         PWM (D 14) PD6 20|        |21  PD7 (D 15) PWM
                          +--------+

## 2.b Pin assignmens for the Vector 3

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
#define X_MAX_PIN          -2

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



#define PROBE_PIN          11     // TX1 on V3
//#define PROBE_PIN          29    //29 on Melzi1284p A2


#define LED_PIN            27

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

