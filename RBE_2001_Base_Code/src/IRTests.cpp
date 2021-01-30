#include <Romi.cpp>//This should handle all required includes
class IRTests{
    private:
Romi robot = Romi();//Create robot object


void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
robot.motherBoard.irSensor.init();
}
void loop(){
//Put your loop code here, to run repeatedly.
robot.motherBoard.irSensor.handleIRsensor();
Serial.println(robot.motherBoard.irSensor.getKeyCode());
delay(25);
}


public:
IRTests(){
    setup();
    while(true){
        loop();
    }
}
};
