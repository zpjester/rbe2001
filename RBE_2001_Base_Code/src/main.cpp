//
#include <Romi.cpp>
#include <blueMotor.h>
#include <arm.h>
#include "Ultrasonic.h"
#include <Timer.h>
Romi robot = Romi();

Arm arm;

Ultrasonic US;
// IRDecoder decoder(14);

enum mainState{start, gripping, lifting, moving, placing, reversing, reset};
int robotState;

int test = 8;

void setup(){
//Put your setup code here, to run once.
robotState = reset;
Serial.begin(9600);
// robot.robotFastInit();

US.setup();
US.loop();
arm.lift.setup();
arm.lift.reset();
arm.lift.liftMotor.setObject(0);
// arm.lift.goDown();
arm.gripper.init();
delay(200);
// robot.drive.driveUltrasonic(10);
}
void loop(){
//Put your loop code here, to run repeatedly.

switch (robotState){
    case start:
    arm.setGripperState(false);
    arm.lift.liftMotor.setObject(2);
    delay(1000);
    robotState++;
    break;
    case gripping:
    delay(500);
    arm.setAngle(PREP25);
    robotState++;
    break;
    case lifting:
    Serial.println(arm.state);    
    if(arm.state == idle){
        robot.drive.driveUltrasonic(DIST25);
        robotState++;
    }
    break;
    case moving:
    if(robot.drive.driveMode == stopped){
        delay(1000);
        arm.setAngle(PLACE25);
        robotState++;
    }
    break;
    case placing:
    if(arm.state == idle){
        arm.setGripperState(true);
        arm.lift.liftMotor.setObject(0);
        robot.drive.driveDist(-10, -10, 0.25);
        robotState++;
    }
    break;
    case reversing:
    if(robot.drive.driveMode == stopped){
        robotState++;
    }
    break;
    case reset:
        arm.setGripperState(true);
        arm.lift.goDown();
        delay(1000);
        robotState = start;
        break;
    
    }




US.loop();
test = US.getDistanceCM();
Serial.println(test);

robot.drive.runDrive();
arm.runArm();
delay(10);
};


