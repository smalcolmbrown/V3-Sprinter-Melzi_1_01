# V3-Sprinter-Melzi_1_01
The original Eaglemoss V3 3D printer firmware cleaned up and modified. 

Nominally called Version 1.01

Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.

based on https://github.com/reprappro/Firmware/tree/master/Sprinter_Melzi
V3 parts http://rp3d.com/ 

Licence: GPL

Arduino 0023 is required for the build and upload.

Almost all V3 specific code and all V3 specific variables have been moved to two new files unsurpringly called V3.cpp and V3.h
added a function to handle the V3 I2C device and the necessay defines 

All instances of V3 specific code on Sprinter_Melzi_Play.pde is now enclosed in #ifdef V3, #else and #endif as required

Some primatives for an I2C Alpha numeric LCD added


look here for descriptions of gcodes: http://reprap.org/wiki/G-code

Implemented Codes

G0  - Coordinated Movement X Y Z E
G1  - Coordinated Movement X Y Z E
G4  - Dwell S<seconds> or P<milliseconds>
G28 - Home all Axis
G90 - Use Absolute Coordinates
G91 - Use Relative Coordinates
G92 - Set current position to cordinates given

RepRap and Custom M Codes
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
M80  - Turn on Power Supply
M81  - Turn off Power Supply
M82  - Set E codes absolute (default)
M83  - Set E codes relative while in Absolute Coordinates (G90) mode
M84  - Disable steppers until next move, 
       or use S<seconds> to specify an inactivity timeout, after which the steppers will be disabled.  S0 to disable the timeout.
M85  - Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
M92  - Set axis_steps_per_unit - same syntax as G92
M104 - Set extruder target temp
M105 - Read current temp
M106 - Fan on
M107 - Fan off
M109 - Wait for extruder current temp to reach target temp.
M114 - Display current position
M115	- Capabilities string
M140 - Set bed target temp
M190 - Wait for bed current temp to reach target temp.
M201 - Set max acceleration in units/s^2 for print moves (M201 X1000 Y1000)
M202 - Set max acceleration in units/s^2 for travel moves (M202 X1000 Y1000)
M203 - Adjust Z height
M205 - Advanced settings

V3 mods for non standard M Codes
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
M238	- Hood Switch Disable
M239 - sends 239 to V3_I2C device, Short Beep
M240 - set Z_MAX_LENGTH_M240
end of V3 mods

M301 - Set PID parameters
