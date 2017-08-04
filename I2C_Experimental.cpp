//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// I2C_Experimental.cpp 
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

#include "SerialManager.h"
#include <stdio.h>
#include <Wire.h>
#include "I2C_Experimental.h"

///////////////////////////////////////////////////////////////////
//
// public functions
//
///////////////////////////////////////////////////////////////////

EI2C_Bus::EI2C_Bus() {
  this->Reset();
}

//////////////////////////////////////////////////////////////////////////
//
// Address( unsigned char dest ) 
//
// Sets the destination address of the I2C. Returns false if the address
// is invalid, true if ok
//
// Suusi M-B 2017/08/01
//
//////////////////////////////////////////////////////////////////////////

boolean EI2C_Bus::Address(byte byAddress) {
  if( byAddress < 8 || byAddress > 127) {
    SerialMgr.cur()->print("Error: ");
    SerialMgr.cur()->print(byAddress);
    SerialMgr.cur()->println(" Bad I2C address (8-127)");
    return false;
  }
  this->m_byAddress = byAddress;
  return true;
}

//////////////////////////////////////////////////////////////////////////
//
// Reset() 
//
// Clears the buffer and sets the counter to buffer Zero. 
//
// Suusi M-B 2017/08/01
//
//////////////////////////////////////////////////////////////////////////

void EI2C_Bus::Reset() {
  this->m_byBufferCount = 0;
  memset(m_byBuffer, 0, sizeof(m_byBuffer));
}

//////////////////////////////////////////////////////////////////////////
//
// Add( byte c )                             // adds a byte to the buffer
// Add( byte bySource[], uint8_t bytes)      // adds a bytes bytes to the buffer
// Add( char str[])                          // adds a string to the buffer
//
// Sends the data specified to the buffer. 
// Returns true if all data added to the buffer, false if not
//
// Suusi M-B 2017/08/01
//
//////////////////////////////////////////////////////////////////////////

boolean EI2C_Bus::Add( const byte c) {
  if (this->m_byBufferCount >= EI2C_BUS_BUFFER_SIZE) {
    return false;
  }
  this->m_byBuffer[this->m_byBufferCount++] = c;
  return true;
}

boolean EI2C_Bus::Add( byte bySource[], byte bytes) {
  if ((this->m_byBufferCount + bytes )>= EI2C_BUS_BUFFER_SIZE) {
    return false;
  }
  while (bytes--) {
    this->Add(*bySource++);
  }
  return true;
}

boolean EI2C_Bus::Add(char str[]) {
  while (char c = *str++) {
    if( !this->Add(c)) {
      return false ;
    }
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////
//
// Send() 
//
// Sends the data in the buffer, Clears the buffer and sets the buffercounter to Zero. 
//
// Suusi M-M 2017/08/01
//
//////////////////////////////////////////////////////////////////////////

void EI2C_Bus::Send() {

  if( this->m_byAddress && this->m_byBufferCount++ ) {
    Wire.beginTransmission(this->m_byAddress);
    Wire.send(this->m_byBuffer, this->m_byBufferCount);
    Wire.endTransmission();

    this->Reset();
  }
}

//////////////////////////////////////////////////////////////////////////
//
// Request(const unsigned char byBytes) 
//
// Sends the data in the buffer, Clears the buffer and sets the buffercounter to Zero. 
//
// Suusi M-M 2017/08/01
//
//////////////////////////////////////////////////////////////////////////

boolean EI2C_Bus::Request(const byte byBytes) {
  if (!this->m_byAddress) {
    return false;
  }
  // requestFrom() is a blocking function
  if (Wire.requestFrom(this->m_byAddress, byBytes) == 0) {
    SerialMgr.cur()->print("Error: ");
    SerialMgr.cur()->print(m_byAddress);
    SerialMgr.cur()->println(" No responce");
    return false;
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////
//
// Relay(const unsigned char bytes) 
//
// Sends the data in the buffer, Clears the buffer and sets the buffercounter to Zero. 
//
// Suusi M-M 2017/08/01
//
//////////////////////////////////////////////////////////////////////////

void EI2C_Bus::Relay(const byte byBytes) {
  if (this->Request(byBytes)) {
    EchoData(byBytes, "i2c-reply", this->m_byAddress);
  }
}

void EI2C_Bus::EchoPrefix(byte byBytes, const char szPrefix[], byte byAddress) {
  SerialMgr.cur()->print(szPrefix);
  SerialMgr.cur()->print(": from:");
  SerialMgr.cur()->print(byAddress);
  SerialMgr.cur()->print(" bytes:");
  SerialMgr.cur()->print(byBytes);
  SerialMgr.cur()->print(" data:");
}

void EI2C_Bus::EchoData(byte byBytes, const char szPrefix[], byte byAddress) {
  EchoPrefix(byBytes, szPrefix, byAddress);
  while (byBytes-- && Wire.available()) {
    SerialMgr.cur()->print(Wire.receive());
  }
  SerialMgr.cur()->println(" ");
}

void EI2C_Bus::EchoBuffer(const char szPrefix[], byte byAddress) {
  EchoPrefix(this->m_byBufferCount, szPrefix, byAddress);
  for (byte i = 0; i < this->m_byBufferCount; i++) {
    SerialMgr.cur()->print(this->m_byBuffer[i]);
  }
  SerialMgr.cur()->println(" ");
}

