#include <Arduino.h>
#include "IRdecoder.h"
class sensors{
    public:
    IRDecoder decoder;
    public:
    sensors(void) : decoder(14) {
    }
    void sensorsInit(void);
/*/
};
/*/  
    String getIRDirectionFromCode(int32_t code, bool compass);
    String getIRDirection(bool compass);   
    sensors();  
};