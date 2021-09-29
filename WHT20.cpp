/***************************************************************************
* File Name: WHT20.cpp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include <Wire.h>
#include "WHT20.h"

WHT20::WHT20 () 
{
  address = WHT20_ADDRESS;
}


WHT20::WHT20 (byte addr) 
{
  address = addr;
}


void WHT20::init () 
{
  Wire.beginTransmission(address);
  Wire.write(byte(0xBE));     //Initialization command
  Wire.write(byte(0x08));   
  Wire.write(byte(0x00));    
  Wire.endTransmission();
}

void WHT20::measure () 
{
  Wire.beginTransmission(address);
  Wire.write(byte(0xAC));      //Trigger measurement
  Wire.write(byte(0x33));   
  Wire.write(byte(0x00));  
  Wire.endTransmission();
}

void WHT20::request () 
{
byte1=0; byte2=0; byte3=0; byte4=0; byte5=0; byte6=0; byte4_half=0;

  Wire.beginTransmission(address);
  Wire.write(byte(0x71));	
  Wire.endTransmission();
  
  Wire.requestFrom(address, 6);
  while (Wire.available())
  {
    byte1 = Wire.read();   //status byte
    byte2 = Wire.read();   //Humidity
    byte3 = Wire.read();   //Humidity
    byte4 = Wire.read();   //Humidity and Temp
    byte5 = Wire.read();   //Temp
    byte6 = Wire.read();   //Temp
  }
}

float WHT20::getTemp () 
{
  long templong=0;

  byte4_half = byte4 << 4; //shift it by 4 bits and place
  byte4_half = byte4_half >> 4; //shift it back by 4bits
  templong = byte4_half;    //place it
  templong = templong << 8;   // shift it by 8 bits
  templong |= byte5;       // place 2nd byte of temp
  templong = templong << 8;   // shift it by 8 bits
  templong |= byte6;       // place 3rd byte of temp

  float tempfloat = (((float)templong/1048576)*200)-50;

  return tempfloat;
}

float WHT20::getHumi () 
{
  long humilong=0;

  humilong = byte2;        // place 1st byte of humidity
  humilong = humilong << 8;   // shift it by 8 bits
  humilong |= byte3;       // place 2nd byte of humidity
  humilong = humilong << 4;   // shift it by 4 bits
  humilong |= byte4;       // place 3rd byte of humidity (4 bit)

  float humifloat = ((float)humilong/1048576)*100;

  return humifloat;
}