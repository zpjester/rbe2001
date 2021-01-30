//
#include <Romi.cpp>

Romi robot = Romi();

void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
// robot.robotFastInit();
robot.sensors.decoder.init();
}
void loop(){
//Put your loop code here, to run repeatedly.
//robot.drive.driveTest(robot.motherBoard.getIRDirection(), 1);
delay(1);
};


/**/