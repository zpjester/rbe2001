
#include "sensors.h";

extern IRDecoder decoder;
void sensors::sensorsInit(){
            decoder.init();
}
String sensors::getIRDirectionFromCode(int32_t code, bool compass){
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
    