#include <Wire.h>
#include <WHT20.h>

WHT20 sensor;           //default I2C address  0x38
//WHT20 sensor(0x48);   //I2C address


void setup() 
{
  Serial.begin(19200);
  Wire.begin();
  
  sensor.init();
  delay(100);
}

void loop() 
{
  sensor.measure();
  delay(75);          //75ms is needed
  sensor.request();
  
  Serial.print(sensor.getTemp());Serial.println(" *C");
  Serial.print(sensor.getHumi());Serial.println(" %");
  Serial.println("-----------");


  delay(1000);
}

