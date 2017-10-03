# V3-Sprinter-Melzi_1_01
The original Eaglemoss V3 3D printer firmware cleaned up and modified.  

Nominally called Version 1.01  

Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.  

Based on https://github.com/reprappro/Firmware/tree/master/Sprinter_Melzi  
V3 parts http://rp3d.com/ and Eaglemoss  
M500, M501, M502, M503 EEPROM Parts by Kliment Sprinter  
Experimenatl I2C bus pinched from MARLIN  
I2C_lcd  Suusi Malcolm-Brown and MARLIN
T0 and T1 Bill Green  

Licence: GPL  

Arduino 0023 is required for the build and upload.  

Almost all V3 specific code and all V3 specific variables have been moved to two new files unsurpringly called V3.cpp and V3.h
added a function to handle the V3 I2C device and the necessay defines  

All instances of V3 specific code on Sprinter_Melzi_Play.pde is now enclosed in #ifdef V3, #else and #endif as required  

I2C_LCD needs F Malpartida's NewLiquidCrystal library. Download the repository from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads and put it in your documents/arduino/libraries folder and restart your ide.  

You need to modify libuary file LiquidCrystal_I2C_ByVac.h to get the program to compile in Arduino 0023  

An already modified version can be downloaded from here. [LiquidCrystal_I2C](https://github.com/smalcolmbrown/LiquidCrystal_I2C)  

Since build 1.01.0105 you will need to install the [LiquidTWI2](https://github.com/lincomatic/LiquidTWI2) library  


**2016/12/19 Build 0100  Changes:**  
Added file **I2C_lcd.h** to contain the I2C lcd specific declarations.  
Added file **I2C_lcd.cpp** to contain the I2C lcd specific functions etc.  
global int btt to store the target heated bed temperature in degrees C.  
global int ett to store the extrude traget temprature in degrees C.  
global bool bFanOn to store fan status: true = on, false = off.  
added a call to SplashScreen() to setup().  
added call to StatusScreen() to funtion gcode_M190() to update status screen whist waiting for the bed to get to temperature.  
added call to StatusScreen() to funtion wait_for_temp() to update status screen whist waiting for the extruder to get to temperature.  

**2017/01/22 Build 0100a  Changes:**  
enabled the code for G29 / G30 G Code Currently residing in the LCD-modifications branch  

**2017/02/24 Build 0100b Changes:**  
Added StatusScreen() to setup()  
Fixed bug in UUID on the LCD SplashScreen() by changing char uuid[] = "0000..." to char pointer uuid = "0000..."  
Merged LCD and master branches  

**2017/02/25 Build 0100c Changes:**  
fixed bug in M190 so LCD displays increasing temperature  
fixed bug in status strings.  

**2017/02/26 Build 0100d Changes:**  
Displaying printer state on LCD **"Sprinter: Idle", "Sprinter: Heating", "Sprinter: Printing", "Sprinter: Done"**  

**2017/02/27 Build 0100e Changes:**  
Fixed Bug in displaying printer state on the LCD.  

**2017/02/28 Build 0101 Changes:**  
Made the check_PauseID() function in V3.cpp more readable through a series of defines in V3.h  
Fixed bug in M109 that was preventing the LCD from displaying the extruder Temperature as it rose from ambient to target temperature.  
Changed printer name from **"Vector 3 3D printer"** to **"Vector 3"**  
fixed centering bug in SplashScreen()  
Displaying printer state on LCD to **"Vector 3: Idle", "Vector 3: Heating", "Vector 3: Printing", "Vector 3: Done"** 

**2017/07/14 Build 0102 Changes:**  
Added **M42** function works on M42 A1 S1 syntax as per Bill Green and M42 P30 S1 as per reprap wikki. A V3 melzi specific version of Klimet's code  

**2017/07/27 Build 0103 Changes:**  
Added functionality from the latest firmware update from Eaglemoss as modified by Chris Holland. Changes include over temperature detection for both hot end and the heated bed and improved thermistor tables  

**2017/08/05 Build 0104 Changes:**  
global int fanSpeeds to store fan speed, 0-255 0 = off, 255 full speed  
global bool bFanOn removed.  
New custom characters to resemble the screens on Marlin LCDs  
New LCD splash screen added  
LCD now displays feed rate percentage and elapsed time  
New PC style beep codes to help diagnose thermistor errors.  
**One long beep** and **one short beep** extruder themistor **low** (open circuit themistor)  
**One long beep** and **two short beeps** heated bed themistor **low** (open circuit themistor)  
**One long beep** and **three short beeps** extruder themistor **high** (short circuit themistor)  
**One long beep** and **four short beeps** heated bed themistor **high** (short circuit themistor)  
New **experimental I2C bus** simplified from Marlin **M260** and **M261**  
New test error conditions **M499**  
Added file **Config_LCD.h** to hold the LCD configeration data  
Added file **I2C_Experimental.h** to hold the experimental I2C data  
Added file **I2C_Experimental.cpp** to hold the experimental I2C code  
Changed char pointer uuid[] = "0000..." back to char uuid[] = "0000..."  

**2017/08/18 Build 0105 Changes:**  
Fixed Feed Rate display to reflect reality.  
Added **M355** - Case light on or off. Operating on on Pin **A1** on J16  
Added theoretical support for the **Panelolu2 LCD** but **NOT** the rotary switch and integrated SD card reader. **Untested!**  
Added file **V3_EEPROM.h** to hold EEPROM data locations making future EEPROM functions easier to implement  
Added **STEPPER_DRIVER_X_Y_DRV8825** switch to allow for Bill Greens stepper driver boards which use **DRV8825** stepper drivers instead of the standard **A4988** stepper drivers for the **X and Y Axis**  
Changed the default value of **nzone** back to 2 from 5. The Jume 2017 Eaglemoss firmware release fixed the themistor tables and cured the problem.
LCD boot screen now shows the Firmware version Major, Minor and Build  

**2017/08/31 Build 0106 changes**  
Fixed coding error in M360 and M361 handling  
Added Bill Green's Tool select patch to allow for two extruders T0 and T1  
Changes to system reporting.

**2017/09/04 Build 0107 changes**  
Removed Tool select patch to allow for two extruders T0 and T1 due to problems with Matter control and S3D  

**2017/09/14 Build 0108**  
fixed T0 and T1  
Hood Switch disable / enable now stored in EEPROM  
bleep mute option in M237 /M238 stored in EEPROM  

**2017/09/23 Build 0109**  
Now stores PID and Ramp acceleration variables in EEPROM  
Now allows max feedrate to be adjusted via M203  
The number of Extruders can now be set in Configuration.h  
Fixed M201 and M202 fixed error in max_acceleration_units_per_sq_second (thanks Bill)  
Fixed Error codes in manager_heater() - now sets them correctly before calling BBB() All previous version including those from Eaglemoss forgot to set the error codes for Bed Temperature High or Low and Extruder temperature high  
  
**2017/10/03 Build 0110**  
Added M601  show Extruder Temp jitter  
Added M602  reset Extruder Temp jitter  
Added M303 PID auto-tune  
Minor bug fixes and streamlined reading Extruder temperature for consistency. 
