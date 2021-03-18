//
#include <Romi.cpp>
#include <blueMotor.h>
#include <arm.h>
#include "Ultrasonic.h"
#include <Timer.h>
Romi robot = Romi();

Arm arm;
enum side{Left, Right};
int robotSide = Left;
Ultrasonic US;
IRDecoder decoder(14);

const int pauseCode = 0;
const int resumeCode = 2;
const int confirmCode = 9;
bool robotPaused = false;
bool awaitConfirm = true;

enum mainState{
    initialize, start,
    collectLift, moveToWall, roofGrab, oldLift,//Grab old panel
    oldToInt, oldTurnToDepot, oldLower, oldMoveToDepot, oldSquareAtDepot, oldDrop,//Place old panel
    waitForNew, newGrab, newLift, newToInt, newTurnToRoof, newToPrep, newToRoof, newPlace, newAdjLeft, newAdjRight, newAdjReturn, newPullBack, newRelease,//grab / place new panel
    emptyToInt, traverseTurn1, traverseDriveToStart, traverseTurn2, traverseCross, traverseTurn3, traverseToInt, traverseTurn4,//traverse
    completed};//done
int robotState;


void setup(){
//Put your setup code here, to run once.
robotState = initialize;
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
    // Serial.println(awaitConfirm);
    return completed;
}


void loop(){
//Put your loop code here, to run repeatedly.


//
switch (robotState){
    case initialize:
    arm.lift.goDown();
    robotState++;
    awaitConfirm = true;
    arm.setGripperState(true);
    break;
    case start:
    
    
    if(stageComplete()){
    arm.setAngle(PLACE45);
    
    robotState++;
    }
    
    break;
    case collectLift:
    if(stageComplete()){
        float dist;
        if(robotSide == Left){
            dist = DIST45PICKUP;
            robot.drive.driveUltrasonic(dist);
        }
        else{
            dist = 9.75;
            robot.drive.driveDist(dist * 0.97, dist, 0.25);
            // while(true){}
        }
        
        robotState++;
    }
    break;
    case moveToWall:
    if(stageComplete()){
        arm.setGripperState(false);
        arm.lift.liftMotor.setObject(2);
        awaitConfirm = true;
       robotState++; 
    }
    break;
    case roofGrab:
    if(stageComplete()){
        float angle;
            angle = PREP25;
        
        arm.setAngle(angle);
        robot.drive.driveDist(-.375, -.375, 0.25);
       robotState++; 
    }
    break;
    case oldLift:
    if(stageComplete()){
        // robot.drive.driveUltrasonic(ROOFINTER);
        if(robotSide == Left){
            robot.drive.driveDist(-5.25, -5.25, 0.2);
        }
        else{
            robot.drive.driveDist(-9.875, -9.875, 0.2);
        }
        
       robotState++; 
    }
    break;
    case oldToInt:
    if(stageComplete()){
        float angle = -(robotSide * 2 - 1) * 90;
        robot.drive.turnAngle(angle, 0.25);  
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
       robotState++; 
    }
    break;
    case oldMoveToDepot:
    if(stageComplete()){
        robot.drive.driveTime(.25, 500);
        awaitConfirm = true;
       robotState++; 
    }
    break;
    case oldSquareAtDepot:
    if(stageComplete()){
        arm.setGripperState(true);
       robotState++; 
    }
    break;
    case oldDrop:
        if(stageComplete()){
            awaitConfirm = true;
            robot.drive.driveDist(-0.1875, -0.1875, 0.25);
            // delay(250);
        robotState++;        
    }
    break;
    case waitForNew:
    if(stageComplete()){
        arm.setGripperState(false);
        robotState++;
    }
    break;
    case newGrab:
    if(stageComplete()){
        arm.setAngle(PREP25);
        robotState++;
    }
    break;
    case newLift:
    if(stageComplete()){
        // robot.drive.driveUltrasonic(DEPOTINTER);
        robot.drive.driveDist(-8.65, -8.65, 0.25);
        robotState++;
    }
    case newToInt:
    if(stageComplete()){
        float angle = (robotSide * 2 - 1) * 90;
        robot.drive.turnAngle(angle, 0.25);
        robotState++;
    }
    break;
    case newTurnToRoof:
    if(stageComplete()){
        float dist;
        if(robotSide == Left){
            dist = DIST45;
            robot.drive.driveUltrasonic(dist);
        }
        else{
            dist = 9.825;
            robot.drive.driveDist(dist, dist, 0.375);
        }
        
        robotState = newToRoof;
    }
    break;
    case newToRoof:
        if(stageComplete()){
            float angle;
            if(robotSide == Left){
                angle = PREP45;
            }
            else{
                angle = PREP25;
            }
            arm.setAngle(angle);
            
            robotState = newToPrep;
        }
        case newToPrep:
    if(stageComplete()){
        
        

        float angle;
        if(robotSide == Left){
            angle = PLACE45;
        }
        else{
            angle = PLACE25;
        }
        awaitConfirm = true;
        arm.setAngle(angle);
        robotState = newPlace;
    }
    break;
    case newPlace:
        if(stageComplete()){            
            // robot.drive.turnAngle(10, 0.5);
            arm.setGripperState(true);
            arm.lift.liftMotor.setObject(0);
            robotState = newRelease;
        }
    break;
    /*
    case newAdjLeft:
    if(stageComplete()){
            robot.drive.turnAngle(-20, 0.5);
            
            robotState++;
    }
    break;
    case newAdjRight:
    if(stageComplete()){
        robot.drive.turnAngle(10, 0.5);
        awaitConfirm = true;
        robotState++;
    }
    case newAdjReturn:
    if(stageComplete()){
        robot.drive.driveTime(-0.5, 0.25);
        robotState++;
    }
    break;
    case newPullBack:
    if(stageComplete()){
        arm.setGripperState(true);
        robotState++;
    }
    break;*/
    case newRelease:
        if(stageComplete()){
            if(robotSide == Left){
            robot.drive.driveDist(-5.75, -5.75, 0.25);
        }
        else{
            robot.drive.driveDist(-5.75, -5.75, 0.25);
        }
            robotState++;
        }
    break;
    case emptyToInt:
        if(stageComplete()){
            if(robotSide == Right){
                robotState = completed;
            }
            else{
                robotState = traverseTurn1;
                robot.drive.turnAngle(90, 0.3);
            }
        }
        break;
    case traverseTurn1:
        if(stageComplete()){
            robot.drive.driveDist(8, 8, .25);
            robotState++;
        }
    break;
    case traverseDriveToStart:
        if(stageComplete()){
            robot.drive.turnAngle(-90, 0.3);
            robotState++;
        }
    break;
    case traverseTurn2:
    if(stageComplete()){
        robot.drive.driveDist(TRAVERSEDIST, TRAVERSEDIST, 0.3);
        robotState++;
        robotSide = Right;
    }
    case traverseCross:
    if(stageComplete()){
        robot.drive.turnAngle(90, 0.3);
        robotState++;
    }
    case traverseTurn3:
    if(stageComplete()){
        robot.drive.driveUltrasonic(DEPOTINTER);
        robotState++;
    }
    case traverseToInt:
    if(stageComplete()){
        robot.drive.turnAngle(90, 0.25);
        robotState++;
    }
    case traverseTurn4:
    if(stageComplete()){
        arm.setAngle(PLACE25);
        robotState = collectLift;
    }

    case completed:
    break;
    }

/**/


int IRCode = decoder.getKeyCode();
if(IRCode >= 0){
    // Serial.println(IRCode);
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


