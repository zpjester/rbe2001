//
#include <Romi.cpp>
<<<<<<< Updated upstream
#include <fourBar.h>
#include <servo32u4.h>
Romi robot = Romi();
fourBar lift;
=======
#include <blueMotor.h>
#include <servo32u4.h>
Romi robot = Romi();
blueMotor armMotor = blueMotor();
>>>>>>> Stashed changes
Servo32U4 gripper = Servo32U4();
// IRDecoder decoder(14);
enum driveType{initialize, driving, turning};
int driveState;
void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
// robot.robotFastInit();
gripper.Attach();
gripper.Init();
lift.setup();
lift.reset();
driveState = initialize;
gripper.Attach();
gripper.Init();
}
void loop(){
//Put your loop code here, to run repeatedly.
lift.goToAngle(PI/2);
gripper.Write(1100);
Serial.println("moving up");
while(!lift.runArm()){
    delay (5);
    // Serial.println(lift.getAngle());
}
Serial.println("moving down");
lift.goToAngle(0);
gripper.Write(1700);
while (!lift.runArm()){
    delay (5);
    // Serial.println(lift.getAngle());
}
delay(500);


};


