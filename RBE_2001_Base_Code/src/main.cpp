//
#include <Romi.cpp>
#include <blueMotor.h>
#include <arm.h>
#include "Ultrasonic.h"
#include <Timer.h>
Romi robot = Romi();

Arm arm;
enum side{Left, Right};
int robotSide = Right;
Ultrasonic US;
IRDecoder decoder(14);

const int pauseCode = 0;
const int resumeCode = 2;
const int confirmCode = 9;
bool robotPaused = false;
bool awaitConfirm = false;

enum mainState{
    start,
    collectLift, moveToWall, roofGrab, oldLift,//Grab old panel
    oldToInt, oldTurnToDepot, oldLower, oldMoveToDepot, oldLowerToDepot, oldDrop,//Place old panel
    newGrab, newToInt, newTurnToRoof, newToPrep, newPlace, newRelease,//grab / place new panel
    emptyToInt, traverseTurn1, traverseDriveToStart, traverseTurn2, traverseCross, traverseTurn3, traverseToInt, traverseTurn4,//traverse
    completed};//done
int robotState;


void setup(){
//Put your setup code here, to run once.
robotState = start;
Serial.begin(9600);
// robot.robotFastInit();

US.setup();
US.loop();
arm.lift.setup();
arm.lift.reset();
arm.lift.liftMotor.setObject(0);
// arm.lift.goDown();
arm.Gripper.init();


decoder.init();
delay(200);
// robot.drive.driveUltrasonic(10);
}


bool stageComplete(){
    
    
    bool completed =  (robot.drive.driveMode == idle) && (arm.state == idle) && !awaitConfirm;
    Serial.println(awaitConfirm);
    return completed;
}


void loop(){
//Put your loop code here, to run repeatedly.


//
switch (robotState){
    case start:
    arm.lift.goDown();
    arm.setGripperState(true);
    arm.setAngle(PLACE45);
    
    robotState++;
    break;
    case collectLift:
    if(stageComplete()){
        float dist;
        if(robotSide == Right){
            dist = DIST45;
        }
        else{
            dist = DIST25;
        }
        robot.drive.driveUltrasonic(dist);
        robotState++;
    }
    break;
    case moveToWall:
    if(stageComplete()){
        arm.setGripperState(false);
        awaitConfirm = true;
       robotState++; 
    }
    break;
    case roofGrab:
    if(stageComplete()){
        float angle;
            angle = PREP25;
        
        arm.setAngle(angle);
       robotState++; 
    }
    break;
    case oldLift:
    if(stageComplete()){
        robot.drive.driveUltrasonic(ROOFINTER);
       robotState++; 
    }
    break;
    case oldToInt:
    if(stageComplete()){
        float angle = -(robotSide * 2 - 1) * 90;
        robot.drive.turnAngle(angle, 0.375);  
       robotState++; 
    }
    break;
    case oldTurnToDepot:
    if(stageComplete()){
        arm.setAngle(IDLECARRY);
       robotState++; 
    }
    break;
    case oldLower:
    if(stageComplete()){
        robot.drive.driveUltrasonic(DEPOTDIST);
        awaitConfirm = true;
       robotState++; 
    }
    break;
    case oldMoveToDepot:
    if(stageComplete()){
        arm.setAngle(DEPOT);
       robotState++; 
    }
    break;
    case oldLowerToDepot:
    if(stageComplete()){
        arm.setGripperState(true);
       robotState++; 
    }
    break;
    case oldDrop:
        if(stageComplete()){
        robotState = completed;
        
    }
    break;
    



    case completed:
    break;
    }

/**/


int IRCode = decoder.getKeyCode();
if(IRCode >= 0){
    Serial.println(IRCode);
}
if(IRCode == pauseCode && !robotPaused){
    robotPaused = true;
    robot.drive.pauseDrive();
    arm.pause();
}
else if(IRCode == resumeCode && robotPaused){
    robotPaused = false;
    robot.drive.resumeDrive();
    arm.resume();
}
else if(IRCode == confirmCode){
    awaitConfirm = false;
}

US.loop();
robot.drive.runDrive();
arm.runArm();
delay(10);
};


