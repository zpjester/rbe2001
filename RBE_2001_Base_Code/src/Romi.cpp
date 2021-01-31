#include <Romi32U4.h>
#include <Arduino.h>
#include <driveBase.cpp>
#include <Gyro.h>
#include "IRdecoder.h"

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

class Sensors{
    public:
    IRDecoder decoder;
    public:
    Sensors(void) : decoder(14) {
    }
    void sensorsInit(void) {
        decoder.init();
        }
/*/
};
/*/  
    String getIRDirectionFromCode(int32_t code){
        if(code == 5){
            return "FORWARDS";
        }
        else if(code == 13){
            return "BACKWARDS";
        }
        else if(code == 8){
            return "LEFT";
        }
        else if(code == 10){
            return "RIGHT";
        }
        else if(code == 9){
            return "STOP";
        }
        else{
            return "NO INPUT";
        }
    };
    String getIRDirection(){
        int32_t code = decoder.getKeyCode();
        return getIRDirectionFromCode(code);
    }
    
    
};

/**/





class Romi{
    public:
    driveBase drive;
    Controller motherBoard;
    Sensors sensors;

    Romi(){
        drive = driveBase();
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
