#include <NBtimer.h>

NBtimer testTimer;

void setup()
{
  Serial.begin(9600);
  testTimer.init(1000);
}

void loop()
{
  Serial.print(testTimer.expired()); Serial.print(" "); Serial.println(testTimer.remaining());
  
  if(testTimer.remaining() < -400) testTimer.addTime(500);
}
