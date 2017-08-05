# Eaglemoss Vector 3 Firmware Technical Guide
# Version 1.01.x

# Contents
## 1. Supported G amd M Codes
   ### 1.a Supported G Codes
   These G Codes are the standard ones supported by the Eaglemoss firmware release.
   ### 1.b New Supported G Codes
   These G codes have been added since the official Eaglemoss firmware release.
   ### 1.c Supported Standard RepRap M Codes
   These M codes are the standard ones supported by the official Eaglemoss firmware release.
   ### 1.d Unique V3 M Codes
   These unofficial non standard M codes are unique to the official Eaglemoss firmware release.
   ### 1.e New Supported Standard M Codes
   These M codes have been added since the official Eaglemoss firmware release.
   ### 1.f New Supported Unofficial M Codes
   These unofficial non standard M codes have been added since the official Eaglemoss firmware release.

## 2. Main board pin out
   ### 2.a Pin definition for the Vector 3
   ### 2.b Pin assignments on the Vector 3

## 3. Official Eaglemoss Firmware releases
   ### 3.a 2016/07/01 Firmware release
   ### 3.b 2017/07/06 Firmware release
   
# Section 1 Supported G and M Codes.

## 1.a Supported G Codes.
These G Codes are the standard ones supported by the Eaglemoss firmware release.
### G0  - Rapid linear Move 
   #### Usage
   G0 and G1 have become merged for efficienccy reasons. For details of **G0** see **G1**

### G1  - Linear Move
   #### Usage
   **G0** and **G1** have become merges for efficienccy reasons.
   
   **G0 Xnnn Ynnn Znnn Ennn Fnnn Snnn**
   
   **G1 Xnnn Ynnn Znnn Ennn Fnnn Snnn**
#### Parameters
   Not all parameters need to be used, but at least one has to be used

   **Xnnn** The position to move to on the X axis

   **Ynnn** The position to move to on the Y axis

   **Znnn** The position to move to on the Z axis

   **Ennn** The amount to extrude between the starting point and ending point

   **Fnnn** The feedrate per minute of the move between the starting point and ending point (if supplied)

#### Examples
G0 X12               ; move to 12mm on the X axis

G0 F1500             ; Set the feedrate to 1500mm/minute

G1 X90.6 Y13.8 E22.4 ; Move to 90.6mm on the X axis and 13.8mm on the Y axis while extruding 22.4mm of material

### G4  - Dwell
   #### Usage
   Pause the machine for a period of time. P for milliseconds and S for seconds
   #### Parameters
   **Pnnn** Time to wait, in milliseconds

   **Snnn** Time to wait, in seconds 
   #### Example
   G4 P200
### G28 -  Move to Origin (Home)
   #### Parameters
   This command can be used without any additional parameters.

   **X Flag** to go back to the X axis origin

   **Y Flag** to go back to the Y axis origin

   **Z Flag** to go back to the Z axis origin
   #### Examples
   G28     ; Home all axes

   G28 X Z ; Home the X and Z axes
### G90 - Use Absolute Coordinates
   #### Example
   G90                          ; All coordinates from now on are absolute relative to the origin of the machine.
   ### G91 - Use Relative Coordinates
   #### Example
   G91                          ; All coordinates from now on are relative to the last position. 
### G92 - Set current position to cordinates given
   #### Parameters
   This command can be used without any additional parameters.

   **Xnnn** new X axis position

   **Ynnn** new Y axis position

   **Znnn** new Z axis position

   **Ennn** new extruder position
   #### Example
   G92 X10 E90                  ; Allows programming of absolute zero point, by reseting the current position to the values specified. 
## 1.b New Supported G Codes
These G codes have been added since the official Eaglemoss firmware release.
### G30 - Single Z-Probe
   ####  Usage
   In its simplest form probes bed at current XY location. Otherwise the bed is probed at the specified location
   #### Parameters
   This command can be used without any additional parameters.

   **Xnnn** X coordinate

   **Ynnn** Y coordinate

   **Znnn** Z coordinate

   **Snnn** Set parameter
   #### Example
   G30                          ; Probe the bed at the current XY position. When the probe is triggered, set the Z coordinate to the probe trigger height.

   G30 S-1                      ; Probe the bed at the current XY position. When the probe is triggered, do not savet the Z coordinate.

   G30 X20 Y50                  ; Probe the bed at X20 Y50 and save the XY coordinates

   G30 X180 Y180 S-1            ; As previous example but just report the height errors
## 1.c Supported Standard RepRap M Codes
These M codes are the standard ones supported by the official Eaglemoss firmware release.
### M20  - List SD card
   ### Useage
   Sends a directory listing from the SD card to the terminal
   #### Parameters
   None
   ### Examples
   M20
   ### Returns
   Begin file list:
   
   SQUARE.G
   
   ZCARRI~2.GCO
   
   End file list
   
   ok
### M21  - Initialise SD card
   ### Useage
   The SD card is initialized. If an SD card is loaded when the machine is switched on, this will happen by default. SD card must be initialized for the other SD functions to work.
   #### Parameters
   None
   ### Examples
   M21      ; initialize the SD card
### M22  - Release SD card
   ### Useage
   The SD card is Release, so further (accidental) attempts to read from it are guaranteed to fail. Helpful, but not mandatory before removing the card physically.
   #### Parameters
   None
   ### Examples
   M22      ; released the SD card
### M23  - Select SD file (M23 filename.g)
   ### Useage
   The file specified as filename.gco (8.3 naming convention is supported) is selected ready for printing.
   #### Parameters
   **filename** the filename.gco of the file that you wish to select
   ### Examples
   M23 filename.gco      ; select filename.gco on the SD card
### M24  - Start/resume SD print
   ### Useage
   The machine prints from the file selected with the M23 command. If the print was previously paused with M25, printing is resumed from that point. To restart a file from the beginning, use M23 to reset it, then M24. When this command is used to resume a print that was paused.
   #### Parameters
   None
   ### Examples
   M24      ; Start/resume SD print
### M25  - Pause SD print
   ### Useage
   The machine pauses printing at the current position within the file. To resume printing, use M24. Do not use this code to pause the print in a G-code file, use M226 instead. Prior to pausing,
   #### Parameters
   None
   ### Examples
   M25      ; Pause SD print
### M26  - Set SD position in bytes
   ### Useage
   Set SD position in bytes ().
   #### Parameters
   **Snnn** File position in bytes
   #### Example
   M26 S12345 ; 
### M27  - Report SD print status
   ### Useage
   Marlin and recent forks of RepRapFirmware report the number of bytes processed in this format, which can be processed by Pronterface:
   #### Parameters
   None
   #### Example
   M27      ; report SD print status
   ### Returns
   If Printing: 
   
   SD printing byte 2134/235422
   
   If not printing:
   
   Not SD printing.
### M28  - Start SD write
   ### Useage
   File specified by filename.gco is created (or overwritten if it exists) on the SD card and all subsequent commands sent to the machine are written to that file.
   #### Parameters
   **filename** the filename.gco of the file that you wish to select
   ### Examples
   M28 filename.gco ; creates a file filename.gco to write data to.
### M29  - Stop SD write
   #### Useage
    Stops the SD card write. Does not do anything.
### M80  - Turn on Power Supply
   #### Useage
   Turns on the ATX power supply from standby mode to fully operational mode. No-op on electronics without standby mode. The code is there, but is inoprative as there is no software control of the V3 power supply.
   #### Parameters
   None
   #### Example
   M80      ; Turn on Power Supply
### M81  - Turn off Power Supply
   #### Useage
   Turns off the ATX power supply. Counterpart to M80.  The code is there, but is inoprative as there is no software control of the V3 power supply.
   #### Parameters
   None
   #### Example
   M81      ; Turn off Power Supply
### M82  - Set E codes absolute
   #### Useage
   Makes the extruder interpret extrusion as absolute positions. This is the default on the V3.
   #### Parameters
   None
   #### Example
   M82      ; Makes the extruder interpret extrusion as absolute positions.
### M83  - Set E codes relative while in Absolute Coordinates (G90) mode
   #### Useage
   Makes the extruder interpret extrusion values as relative positions. power supply.
   #### Parameters
   None
   #### Example
   M83      ; Set E codes relative while in Absolute Coordinates
### M84  - Disable steppers until next move, or use S<seconds> to specify an inactivity timeout, after which the steppers will be disabled.  S0 to disable the timeout.
### M85  - Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
### M92  - Set axis_steps_per_unit - same syntax as G92
### M104 - Set extruder target temp
   #### useage
   Set the temperature of the extruder to 190 C and return control to the host immediately (i.e. before that temperature has been reached by the extruder).
   #### Parameters
   **Snnn** the Target temperature in degrees C for the extruder   
   #### Example
   M104 S190 ; sets the extruder target temparture to 190 degrees C
### M105 - Read current temp
### M106 - Fan on
   ### Useage
   Switches the work cooling fan on
   #### Parameters
   This command can be used without any additional parameters.
   
   **Snnn** Fan speed (0 to 255)
   ### Examples
   M107     ; switch work cooling fan off
### M107 - Fan off
   ### Useage
   Switches the work cooling fan off
   #### Parameters
   None
   ### Examples
   M107     ; switch work cooling fan off
### M109 - Set Extruder Temperature and Wait
   #### useage
   Sets Extruder Temperature and wait for extruder current temp to reach target temp.
   #### Parameters
   **Snnn** the Target temperature in degrees C for the extruder   
   #### Example
   M109 S190 ; Sets the extruder target temparture to 190 degrees C
### M114 - Get Current Position
   #### useage
   This causes the RepRap machine to report its current X, Y, Z and E coordinates to the host.
   #### Parameters
   None
   #### Example
   M114     ; Get Current Position
   ### Returns
   X:0.00 Y:0.00 Z:0.00 E:0.00
### M115 - Get Firmware Version and Capabilities
   #### useage
   Request the Firmware Version and Capabilities of the current microcontroller The details are returned to the host computer as key:value pairs separated by spaces and terminated with a linefeed.
   #### Parameters
   None.
   #### Example
   M115     ; Get Firmware Version and Capabilities
   ### Returns
   sample data from firmware:
   
   ok PROTOCOL_VERSION:1.01.0104 FIRMWARE_NAME:Sprinter FIRMWARE_URL:https%3A//github.com/smalcolmbrown/V3-Sprinter-Melzi_1_01/ MACHINE_TYPE:Vector 3 EXTRUDER_COUNT:1 UUID:00000000-0000-0000-0000-000000000000
### M119 - Report endstops status.
### M140 - Set Bed Temperature (Fast)
   #### useage
   Set the temperature of the Heated bed and return control to the host immediately (i.e. before that temperature has been reached by the heated bed).
   #### Parameters
   **Snnn** the Target temperature in degrees C for the heated bed   
   #### Example
   M140 S50  ; sets the heated bed target temparture to 50 degrees C
### M190 - Wait for bed temperature to reach target temp
   #### useage
   Sets heated bed Temperature and wait for extruder current temp to reach target temp.
   #### Parameters
   **Snnn** the Target temperature in degrees C for the heated bed   
   #### Example
   M109 S50 ; Sets the heated bed target temparture to 50 degrees C
### M201 - Set max printing acceleration
   #### useage
   Sets the acceleration that axes can do in units/second^2 for print moves. For consistency with the rest of G Code movement this should be in units/(minute^2), but that gives really silly numbers and one can get lost in all the zeros. So for this we use seconds.
   #### Parameters
   **Xnnn** Acceleration for X axis
   **Ynnn** Acceleration for Y axis
   **Znnn** Acceleration for Z axis
   **Ennn** Acceleration for extruder drives
   #### Example
   M201 X1000 Y1000 Z100 E2000
### M202 - Set max travel acceleration
   #### useage
   Set max travel acceleration in units/s^2 for travel moves (M202 X1000 Y1000).
   #### Parameters
   **Xnnn** Acceleration for X axis
   **Ynnn** Acceleration for Y axis
   **Znnn** Acceleration for Z axis
   **Ennn** Acceleration for extruder drives
   #### Example
   M201 X1000 Y1000 Z100 E2000
### M301 - Set PID parameters
#### Useage
   Setting the PID parameters. Reports the current settings.
#### Parameters
   This command can be used without any additional parameters.
   
   **Pnnn** proportional (Kp)
   
   **Innn** integral (Ki)
   
   **Dnnn** derivative (Kd)
   
   **Fnnn** pid max
   
   **Znnn** nzone
   
   **Wnnn** pid_i_max
   #### Examples
   M301             ; returnes the 
   M301 P1 I2 D3    ; 
   #### Responce
   Snnn,Verbose Status          ; if no error
   
   Snnn,Verbose Status          ; if error
   
   EC:nnn,Verbose Error

## 1.d Unique V3 M Codes
These unofficial non standard M codes are unique to the official Eaglemoss firmware release.
### M4   - Query Status.
   #### Usage
   Querries the Status
   #### Parameters
   None
   #### Example
   M4                           ; returns machien status and error code if set
   #### Responce
   Snnn,Verbose Status          ; if no error
   
   Snnn,Verbose Status          ; if error
   
   EC:nnn,Verbose Error
### M5   - Reset Status and Clears Error flag.
   #### Usage
   Resets the status flag and clears error flag if set
   #### Parameters
   None
   #### Example
   M5                           ; Reset Status and Clears Error flag.
### M211 - Set extruder LED Red LED
   #### Usage
   Sets the extruder LED Red. Sends 211 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M211                          ; Set extruder LED Red.
### M212 - Set extruder LED Red flashing
   #### Usage
   Sets the extruder LED Red flashing. Sends 212 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M212                          ; Set extruder LED Red flashing.
### M213 - Set extruder LED Green
   #### Usage
   Sets the extruder LED Green. Sends 213 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M213                          ; Set extruder LED Green.
### M214 - Set extruder LED Green flashing
   #### Usage
   Sets the extruder LED Green flashing. Sends 214 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M214                          ; Set extruder LED Green flashing.
### M215 - Set extruder LED Blue
   #### Usage
   Sets the extruder LED blue. Sends 215 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M215                          ; Set extruder LED blue.
### M216 - Set extruder LED Blue flashing
   #### Usage
   Sets the extruder LED Blue flashing. Sends 216 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M216                          ; Set front button LED Blue flashing.
### M217 - Set extruder LED White
   #### Usage
   Sets the extruder LED white. Sends 217 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M217                          ; Set extruder LED white.
### M218 - Set extruder LEd White flashing
   #### Usage
   Sets the extruder LED White flashing. Sends 218 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M218                          ; Set extruder LED White flashing.
### M219 - Set extruder LED Orange
   #### Usage
   Sets the extruder LED Orange. Sends 219 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M219                          ; Set extruder LED Orange.
### M220 - Set extruder LED Orange flashing
   #### Usage
   Sets the extruder LED Orange flashing. Sends 220 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M220                          ; Set extruder LED Orange flashing.
### M221 - Set extruder Head LED OFF
   #### Usage
   Sets the extruder LED off. Sends 221 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M221                          ; Set extruder LED off.
### M222 - Set front button LED Red
   #### Usage
   Sets the front button LED red. Sends 222 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M222                          ; Set front button LED red.
### M223 - Set front button LED Red Flashing
   #### Usage
   Sets the front button LED Red Flashing. Sends 223 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M223                          ; Set front button LED Red Flashing.
### M224 - Set front button LED Green
   #### Usage
   Sets the front button LED Green. Sends 224 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M224                          ; Set front button LED Green.
### M225 - Set front button LED Green flashing
   #### Usage
   Sets the front button LED Green flashing. Sends 225 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M225                          ; Set front button LED Green flashing.
### M226 - Set front button LED Blue
   #### Usage
   Sets the front button LED blue. Sends 226 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M226                          ; Set front button LED blue.
### M227 - Set front button LED Blue flashing
   #### Usage
   Sets the front button LED blue flashing. Sends 227 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M227                          ; Set front button LED blue flashing.
### M228 - Set front button LED White
   #### Usage
   Sets the front button LED White. Sends 228 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M228                          ; Set front button LED White.
### M229 - Set front button LED White flashing
   #### Usage
   Sets the front button LED  White flashing. Sends 229 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M229                          ; Set front button LED  White flashing.
### M230 - Set front button LED Orange
   #### Usage
   Sets the front button LED Orange. Sends 230 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M230                          ; Set front button LED Orange.
### M231 - Set front button LED Orange flashing
   #### Usage
   Sets the front button LED Orange flashing. Sends 231 to V3_I2C device. 
   #### Parameters
   None.
   #### Example 
   M231                          ; Set front button LED Orange flashing.
### M232 - Turn front button front LED OFF
   #### Usage
   Turns the front button front LED OFF. Sends 232 to V3_I2C device.
   #### Parameters
   None.
   #### Example 
   M232                          ; Turn front button front LED OFF.
### M233 - 3 short beeps
   #### Usage
   3 short beeps. Sends 233 to V3_I2C device. 
   #### Parameters
   None.
   #### Example 
   M233                          ; 3 short beeps.
### M234 - Long Beep
   #### Usage
   One long beep lasting 3 seconds. Sends 234 to V3_I2C device, 
   #### Parameters
   None.
   #### Example 
   M234                          ; Long beep.
### M235 - Beep every second for 3 min.
   #### Usage
   Beep every second for 3 minuites.
   #### Parameters
   None.
   #### Example 
   M235                          ; Beep every second for 3 minuites.
### M236 - Beep Off
   #### Usage
   Switches beep off. Sends 236 to V3_I2C device. 
   #### Parameters
   None.
   #### Example 
   M236                          ; switches beep off
### M237 - Hood switch warning buzzer enable
   #### Usage
   Enables the hood switch buzzer warning.
   #### Parameters
   None.
   #### Example 
   M237                          ; Enables hood switch buzzer warning
### M238 - Hood switch warning buzzer disable
   #### Usage
   Disables the hood switch buzzer warning.
   #### Parameters
   None.
   #### Example 
   M238                          ; Disables hood switch buzzer warning
### M239 - Short Beep
   #### Usage
   Short Beep. Sends 239 to V3_I2C device, 
   #### Parameters
   None.
   #### Example 
   M239                          ; Short beep
### M240 - set Z_MAX_LENGTH_M240
   #### Usage
   Sets or reads the stored the max Z Height parameter in to the EEPROM
   #### Parameters
   This command can be used without any additional parameters.
  
   **Znnn** the Max Z height

   #### Examples
   M240 Z129.2   ; sets the max Z height to 129.2
   
   M240          ; returns the max z height from the EEPROM
## 1.e New Supported Standard M Codes
These M codes have been added since the official Eaglemoss firmware release.
### M42  - Switch I/O pin
   #### Usage
   Sets or reads the stored the max Z Height parameter in to the EEPROM
   #### Parameters
   There are two distinct syntaxes for this command 1 standard and the other rather non standard both are equally valid
   #### Syntanx 1 - Standard M code syntax
   **Pnnn** Pin number - 27(A4), 28(A3), 29(A2) or 30(A1)
   
   **Snnn** Pin value  -  0 = off, 1 = on.

   #### Examples
   M42 M42 P30 S1 This turns pin A1 on.
   
   M42 M42 P30 S1 This turns pin A1 on.
   #### Syntanx 3 - Melzi specific syntax
   **Annn** Pin number - A1, A2, A3 or A4
   
   **Snnn** Pin value  - 0 = off, 1 = on.

   #### Examples
   M42 A1 S1 ; This turns pin A1 on.
   
   M42 A1 S0 ; This turns pin A1 off
   ### Date implementation
   2017/07/16
### M203 - Record Z adjustment
   ### Useage
   This records a Z offset in non-volatile memory in RepRap's microcontroller where it remains active until next set, 
even when the power is turned off and on again.
   If the first layer is too close to the bed, you need to effectively move the bed down, so the Z value will be negative.
   If the nozzle is too far from the bed during the first layer, the Z value should be positive to raise the bed. 
   The maximum adjustment is +/-1.27mm.
   #### Parameters
   **Znnn** the Max Z adjustment
   #### Example: 
   M203 Z-0.75  ;
### M260 - i2c Send Data
   #### Usage
   Buffer and send data over the i2c bus. Use A to set the address from 0-127. Add up to 32 bytes to the buffer with each B. Send and reset the buffer with S. Pinched from Marlin 1.1.x  Does not act as a slave device
   #### Parameters
   **Annn** The I2C address to send data to
   
   **Bnnn** The data to put into the buffer
   
   **Snnn** Sends the data in the buffer to the I2C address
   #### Examples
   M260 A5 B65 S1 ; Send 'A' to Address 5 now
   
   M260 A39       ; Set address to device I2C address 0x27
   
   M260 B83       ; Add 'S' to the buffer
   
   M260 B112      ; Add 'p' to the buffer
   
   M260 B114      ; Add 'r' to the buffer
   
   M260 B108      ; Add 'i' to the buffer
   
   M260 B105      ; Add 'n' to the buffer
   
   M260 B110      ; Add 't' to the buffer
   
   M260 B110      ; Add 'e' to the buffer
   
   M260 B110      ; Add 'r' to the buffer
   
   M260 S1        ; Send the current buffer
   ### Date implemented
   2017/08/04
### M261 - i2c Request Data
   #### Usage
   Request data from an i2c slave device. This command simply relays the received data to the host. Does not act as a slave device
   #### Parameters
   **Annn** The I2C address to get data from
   
   **Bnnn** The number of bytes to request from the I2C address
   
   #### Example
   M261 A99 B5 ; Request 5 bytes from Address 99
   ### Date implemented
   2017/08/04
## 1.f New Supported Unofficial M Codes
These unofficial non standard M codes have been added since the official Eaglemoss firmware release.
### M499 - Force Error
   #### Usage
   Sets the status and error codes for testing error handler and beep codes
   #### Example
   M499 E1 ; Sets the Status flag to error and the error code to Extruder thermistor open circuit...
   M499 E2 ; Sets the Status flag to error and the error code to Heated Bed thermistor open circuit...
   M499 E3 ; Sets the Status flag to error and the error code to Extruder thermistor short circuit...
   M499 E4 ; Sets the Status flag to error and the error code to Heated Bed thermistor short circuit...
   ### Date implemented
   2017/08/04





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

# 3. Official Eaglemoss Firmware releases
   ## 3.a 2016/07/01 Firmware release
   ## 3.b 2017/07/06 Firmware release
