//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// I2C_Experimental.h 
//
// largely pinched from Marlin 1.1 
//
// Date:      2017/07/02
// Mods By:   Suusi Malcolm-Brown
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#ifndef I2C_EXPERIMENTAL_H
  #define I2C_EXPERIMENTAL_H

#define EI2C_BUS_BUFFER_SIZE 32

class EI2C_Bus {
  private:
    byte    m_byAddress;                                   // the dstination address for buffer
    byte    m_byBuffer[EI2C_BUS_BUFFER_SIZE];              // buffer for data to send
    byte    m_byBufferCount ;                              // number of bytes in buffer
  public:
    EI2C_Bus();                                            // constructor
    boolean Address(const byte byAddress);                 // the I2C destination address
    byte    Address() { return m_byAddress ; }             // returns the address
    boolean Add(byte c );                                  // adds a char to the buffer
    boolean Add(char szString[]);                          // adds a zerp terminated string to the buffer
    boolean Add(byte szBuf[], byte byBytes);                   // adds num chars from buffer 
    void    Send();                                        // sends buffer to I2C destination address then clears the buffer
    void    Reset();                                       // clears the buffer
    boolean Request(const byte bBytes);                     // 
    void    Relay(byte byBytes);                           // 
    void    EchoPrefix(byte byBytes, const char szPrefix[], byte byAddress);
    void    EchoData(byte byBytes, const char szPrefix[], byte byAddress);
    void    EchoBuffer(const char szPrefix[], byte byAddress);
};
  
  
  
  
#endif
