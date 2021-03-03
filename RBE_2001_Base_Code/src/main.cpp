//
#include <Romi.cpp>

Romi robot = Romi();
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
switch (driveState){
    case initialize:
    robot.drive.driveDist(6, 6, 0.375);
    driveState = driving;
    break;
    case driving:
    if(robot.drive.runDrive()){
        robot.drive.stopDrive();
        delay(500);
        robot.drive.turnAngle(90, .25);
        driveState = turning;
    };
    break;
    case turning:
    if(robot.drive.runDrive()){
        robot.drive.stopDrive();
        delay(500);
        robot.drive.driveDist(6, 6, .375);
        driveState = driving;
    };
    
}


delay(1);
};


