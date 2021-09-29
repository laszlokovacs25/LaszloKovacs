/***************************************************************************
* File Name: WHT20.h
* Processor/Platform: Arduino nano (tested)
                      ESP32 wroom (tested)
* Development Environment: Arduino 1.8.9
*
* **************************************************************************/

#ifndef WHT20_h
#define WHT20_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define WHT20_ADDRESS 0x38


class WHT20 
{
  byte byte1=0, byte2=0, byte3=0, byte4=0, byte5=0, byte6=0, byte4_half=0;
  
public:
    WHT20 ();
    WHT20 (byte);
    int address;
    void init ();
    void measure ();
    void request ();
    float getTemp ();
    float getHumi ();
};

#endif
