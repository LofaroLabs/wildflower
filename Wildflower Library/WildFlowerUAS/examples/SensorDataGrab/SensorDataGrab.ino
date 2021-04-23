#include "WildFlowerUAS.h"

SENSORS sense = SENSORS();

void setup() 
{
  Serial.begin(9600);
  sense.Initialize();
}

void loop() 
{
  delay(100);
  sense.ReadCloseRangeLIDAR();
  delay(1000);
  sense.ReadLongRangeLIDAR();
  delay(1000);
  sense.ReadIMU();
  delay(1000);
}
