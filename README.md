# V3-Sprinter-Melzi-Play
The original Eaglemoss V3 3D printer firmware cleaned up and modified. 

arduino 0023 is required for the build and upload.

almost all V3 specific and all V3 specific variables have been moved to two new files unsurpringly called V3.cpp and V3.h
added a function to handle the V3 I2C device and the necessay defines 

all instances of V3 specific code on Sprinter_Melzi_Play.pde is now enclosed in #ifdef V3, #else and #endif as required
