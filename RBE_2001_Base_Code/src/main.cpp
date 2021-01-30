/*/
#include <Romi32U4.h>
#include "IRdecoder.h"
//#include "RemoteConstants.h"

const uint8_t IR_PIN = 14;

Romi32U4Motors motors;

IRDecoder decoder(IR_PIN);

void setup()
{
  decoder.init();
}

void loop()
{ 
  delay(1);
  int32_t keyCode = decoder.getKeyCode();

  if(keyCode >= 0)
  {
    Serial.print(keyCode); 
    Serial.print('\n');
  }
}
/**/