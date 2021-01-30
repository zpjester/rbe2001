#include <Romi32U4.h>
#include <Arduino.h>
#include <driveBase.cpp>
#include <Gyro.h>
#include <IRdecoder.h>

class Controller{
    public:
    Romi32U4ButtonA buttonA;
    Romi32U4ButtonB buttonB;
    Romi32U4ButtonC buttonC;
    Gyro gyro;
    IRDecoder irSensor;
    Controller(){
        buttonA = Romi32U4ButtonA();
        buttonB = Romi32U4ButtonB();
        buttonC = Romi32U4ButtonC();
        gyro = Gyro();
        irSensor = IRDecoder();
        //irSensor.init();
    }
    String getIRDirection(){
        return "";
    };
};

class Romi{
    public:
    driveBase drive;
    Controller motherBoard;

    Romi(){
        drive = driveBase();
        motherBoard = Controller();
    };
};
