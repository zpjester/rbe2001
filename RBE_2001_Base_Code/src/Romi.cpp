#include <Romi32U4.h>
#include <Arduino.h>
#include <driveBaseV2.h>
#include <Gyro.h>
#include "IRdecoder.h"
#include <sensors.h>

class Controller{
    public:
    Romi32U4ButtonA buttonA;
    Romi32U4ButtonB buttonB;
    Romi32U4ButtonC buttonC;
    Gyro gyro;
    Controller(){
        buttonA = Romi32U4ButtonA();
        buttonB = Romi32U4ButtonB();
        buttonC = Romi32U4ButtonC();
        gyro = Gyro();
        
    }
   
    void controllerInit(){//Full setup
        gyro.setup();
        controllerFastInit();
    }
    void controllerFastInit(){//Skip gyro
        decoder.init();
    }
};



/**/





class Romi{
    public:
    driveBaseV2 drive;
    Controller motherBoard;
    sensors sensors;

    Romi(){
        drive = driveBaseV2();
        motherBoard = Controller();
    };
    void robotInit(){
        //main robot init here;
        motherBoard.controllerInit();
        sensors.sensorsInit();
    }
    void robotFastInit(){
        //main robot init here
        motherBoard.controllerFastInit();
        sensors.sensorsInit();
    }
};
