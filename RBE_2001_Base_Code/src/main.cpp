//
#include <Romi.cpp>

Romi robot = Romi();
IRDecoder decoder(14);

void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
robot.motherBoard.buttonA.waitForPress();
delay(1000);
robot.drive.driveDistance(10);
delay(500);
 robot.drive.turnAngle(180);
delay(500);
// robot.drive.driveDistance(10);
delay(500);
// robot.drive.turnAngle(180);
Serial.println("Drive complete");
robot.robotFastInit();
}
void loop(){
//Put your loop code here, to run repeatedly.
int32_t keyCode = decoder.getKeyCode();

//Arcade drive using IR remote
//
    String currCommand = robot.sensors.getIRDirectionFromCode(keyCode, true);
    if(keyCode >= 0){Serial.println(currCommand);}
    robot.drive.directionalDrive(currCommand, 1);
/*/



/**/
delay(1);
};


