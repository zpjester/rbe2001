//
#include <Romi.cpp>
#include <blueMotor.h>
Romi robot = Romi();
blueMotor armMotor = blueMotor();
// IRDecoder decoder(14);
enum driveType{initialize, driving, turning};
int driveState;
void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
// robot.robotFastInit();
driveState = initialize;
}
void loop(){
//Put your loop code here, to run repeatedly.
armMotor.setEffort(1);
delay(500);
armMotor.setEffort(-1);
delay(500);


};


