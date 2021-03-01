//
#include <Romi.cpp>

Romi robot = Romi();
// IRDecoder decoder(14);
enum driveType{initialize, driving, turning};
int driveMode;
void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
// robot.robotFastInit();
driveMode = initialize;
}
void loop(){
//Put your loop code here, to run repeatedly.
switch (driveMode){
    case initialize:
    robot.drive.driveDist(6, 6, 0.375);
    driveMode = driving;
    break;
    case driving:
    if(robot.drive.runDrive()){
        robot.drive.stopDrive();
        delay(500);
        robot.drive.turnAngle(90, .375);
        driveMode = turning;
    };
    break;
    case turning:
    if(robot.drive.runDrive()){
        robot.drive.stopDrive();
        delay(500);
        robot.drive.driveDist(6, 6, .375);
        driveMode = driving;
    };
    
}


delay(1);
};


