//
#include <Romi.cpp>

Romi robot = Romi();
IRDecoder decoder(14);

void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
// robot.robotFastInit();
// robot.sensors.sensorsInit();
// decoder.init();

robot.robotFastInit();
}
void loop(){
//Put your loop code here, to run repeatedly.
int32_t keyCode = decoder.getKeyCode();
//if(keyCode >= 0){
    String currCommand = robot.sensors.getIRDirectionFromCode(keyCode);
    Serial.println(currCommand);
    robot.drive.driveTest(currCommand, 1);
// }
delay(1);
};


/**/