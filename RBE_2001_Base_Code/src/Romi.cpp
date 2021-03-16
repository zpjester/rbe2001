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
    String getIRDirectionFromCode(int32_t code, bool compass){
        if(!compass){
            switch(code){
                case 5:
                return "FORWARDS";
                case 13:
                return "BACKWARDS";
                case 8:
                return "LEFT";
                case 10:
                return "RIGHT";
                case 9:
                return "STOP";
                default:
                return "NO INPUT";
            }
        }
        else{
          switch(code){
                case 5:
                return "NORTH";
                case 13:
                return "SOUTH";
                case 8:
                return "WEST";
                case 10:
                return "EAST";
                case 6:
                return "NORTHEAST";
                case 14:
                return "SOUTHEAST";
                case 12:
                return "SOUTHWEST";
                case 4:
                return "NORTHWEST";
                case 9:
                return "STOP";
                default:
                return "NO INPUT";
            }  
        }
        
    };
    String getIRDirection(bool compass){
        int32_t code = decoder.getKeyCode();
        return getIRDirectionFromCode(code, compass);
    }
    
    
};

/**/





class Romi{
    public:
    driveBase drive;
    Controller motherBoard;
<<<<<<< Updated upstream
    Sensors sensors;

=======
    RomiSensors sensors;
    
>>>>>>> Stashed changes
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
