
#include <Romi.cpp>
#include <fourBar.h>
Romi robot = Romi();

IRDecoder decoder(14);


fourBar lift;
// Servo32U4 gripper = Servo32U4();
Romi32U4ButtonA pbA = Romi32U4ButtonA();
// IRDecoder decoder(14);
enum driveType{initialize, driving, turning};
int driveState;

void setup(){
    pinMode(1, INPUT_PULLUP);
//Put your setup code here, to run once.
Serial.begin(9600);

robot.robotFastInit();

// robot.robotFastInit();
// gripper.Attach();
// gripper.Init();
// lift.setup();
// lift.reset();
driveState = initialize;
// while(!pbA.isPressed()){
// lift.liftMotor.setEffort(400);
// }
delay(2000);
lift.liftMotor.setObject(0);
lift.liftMotor.setEffort(-200);
while(digitalRead(1) == 1){
    // Serial.println(digitalRead(0));

}
lift.liftMotor.reset();
lift.liftMotor.setEffort(0);

lift.liftMotor.setObject(0);
lift.goToAngle(90);


}
void loop(){






};


