//
#include <Romi.cpp>
#include <fourBar.h>
Romi robot = Romi();
fourBar lift;
// IRDecoder decoder(14);
enum driveType{initialize, driving, turning};
int driveState;
void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
// robot.robotFastInit();
lift.setup();
lift.reset();
driveState = initialize;
}
void loop(){
//Put your loop code here, to run repeatedly.
lift.goToAngle(PI/2);
Serial.println("moving up");
while(!lift.runArm()){
    delay (5);
    // Serial.println(lift.getAngle());
}
Serial.println("moving down");
lift.goToAngle(0);
while (!lift.runArm()){
    delay (5);
    // Serial.println(lift.getAngle());
}
delay(500);


};


