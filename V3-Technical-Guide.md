Eaglemoss Vector 3 Technical Guide

Contents

1. Supported G Codes

2. Main board pin out




Section 1 Supported G Codes.

The following G Codes have been implemented

G0  -> G1
G1  - Coordinated Movement X Y Z E
G4  - Dwell S<seconds> or P<milliseconds>
G28 - Home all Axis
G30 - Single Z-Probe
G90 - Use Absolute Coordinates
G91 - Use Relative Coordinates
G92 - Set current position to cordinates given

RepRap and Custom M Codes

M4   - Query Status.                       (V3 only)
M5   - Reset Status and Clears Error flag. (V3 only)
M20  - List SD card
M21  - Init SD card
M22  - Release SD card
M23  - Select SD file (M23 filename.g)
M24  - Start/resume SD print
M25  - Pause SD print
M26  - Set SD position in bytes (M26 S12345)
M27  - Report SD print status
M28  - Start SD write (M28 filename.g)
M29  - Stop SD write does not do anything.
M42  - Switch I/O pin
M80  - Turn on Power Supply
M81  - Turn off Power Supply
M82  - Set E codes absolute (default)
M83  - Set E codes relative while in Absolute Coordinates (G90) mode
M84  - Disable steppers until next move, or use S<seconds> to specify an inactivity timeout, after which the steppers will be disabled.  S0 to disable the timeout.
M85  - Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
M92  - Set axis_steps_per_unit - same syntax as G92
M104 - Set extruder target temp
M105 - Read current temp
M106 - Fan on
M107 - Fan off
M109 - Wait for extruder current temp to reach target temp.
M114 - Display current position
M115 - Capabilities string
M119 - Report endstops status.
M140 - Set bed target temp
M190 - Wait for bed current temp to reach target temp.
M201 - Set max acceleration in units/s^2 for print moves (M201 X1000 Y1000)
M202 - Set max acceleration in units/s^2 for travel moves (M202 X1000 Y1000)
M203 - Adjust Z height
M205 - Advanced settings
M211 - sends 211 to V3_I2C device, extruder Red LED on
M212 - sends 212 to V3_I2C device, extruder Red LED flashing
M213 - sends 213 to V3_I2C device, extruder Green LED on
M214 - sends 214 to V3_I2C device, extruder Green LED flashing
M215 - sends 215 to V3_I2C device, extruder Blue LED on
M216 - sends 216 to V3_I2C device, extruder Blue LED flashing
M217 - sends 217 to V3_I2C device, extruder White LED on
M218 - sends 218 to V3_I2C device, extruder White LED flashing
M219 - sends 219 to V3_I2C device, extruder Orange LED on
M220 - sends 220 to V3_I2C device, extruder Orange LED flashing
M221 - sends 221 to V3_I2C device, extruder Head LED OFF
M222 - sends 222 to V3_I2C device, front button LED Red
M223 - sends 223 to V3_I2C device, front button LED Red Flashing
M224 - sends 224 to V3_I2C device, front button LED Green
M225 - sends 225 to V3_I2C device, front button LED Green flashing
M226 - sends 226 to V3_I2C device, front button LED Blue
M227 - sends 227 to V3_I2C device, front button LED Green flashing
M228 - sends 228 to V3_I2C device, front button LED White
M229 - sends 229 to V3_I2C device, front button LED White flashing
M230 - sends 230 to V3_I2C device, front button front LED Orange
M231 - sends 231 to V3_I2C device, front button front LED Orange flashing
M232 - sends 232 to V3_I2C device, front button front LED OFF
M233 - sends 233 to V3_I2C device, Short Beep x 3
M234 - sends 234 to V3_I2C device, Long Beep x 1 ( 3 sec)
M235 - sends 235 to V3_I2C device, Beep every sec, 3 min.
M236 - sends 236 to V3_I2C device, Beep Off
M237 - Hood Switch Enable
M238 - Hood Switch Disable
M239 - sends 239 to V3_I2C device, Short Beep
M240 - set Z_MAX_LENGTH_M240
M301 - set PID parameter

Section 2 The pin asignments

2.a Pin definition for the Melzi

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
