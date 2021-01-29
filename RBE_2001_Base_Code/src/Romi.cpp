#include <Romi32U4.h>
#include <Arduino.h>
#include <driveBase.cpp>
class Romi{
    public:
    driveBase drive;
    
    Romi(){
        drive = driveBase();
    };
};