//
#include <Romi.cpp>

Romi robot = Romi();
<<<<<<< Updated upstream
IRDecoder decoder(14);

=======
fourBar lift;
Servo32U4 gripper = Servo32U4();
Romi32U4ButtonA pbA = Romi32U4ButtonA();
// IRDecoder decoder(14);
enum driveType{initialize, driving, turning};
int driveState;
>>>>>>> Stashed changes
void setup(){
    pinMode(1, INPUT_PULLUP);
//Put your setup code here, to run once.
Serial.begin(9600);
<<<<<<< Updated upstream
robot.robotFastInit();
=======
// robot.robotFastInit();
gripper.Attach();
gripper.Init();
lift.setup();
lift.reset();
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
lift.liftMotor.setEffort(0);

lift.liftMotor.setObject(0);

>>>>>>> Stashed changes
}
void loop(){
    int times[41];
    int inEff[41];
    int outEff[41];
    float vel[41];
    pbA.waitForPress();
    pbA.waitForRelease();
    lift.liftMotor.reset();
//Put your loop code here, to run repeatedly.
<<<<<<< Updated upstream
int32_t keyCode = decoder.getKeyCode();

//Arcade drive using IR remote
//
    String currCommand = robot.sensors.getIRDirectionFromCode(keyCode, true);
    if(keyCode >= 0){Serial.println(currCommand);}
    robot.drive.directionalDrive(currCommand, 1);
/*/


=======
long int startTime = millis();
for(int i = 0; i <410; i+=10){
long int time = millis() - startTime;
// Serial.print("Time = ");
// Serial.print(time);
// Serial.print(", Input Effort = ");
// Serial.print(i);
// Serial.print(", Applied Effort = ");
int applEffort = lift.liftMotor.setEffortDBand(i);
// Serial.print(applEffort);
// Serial.print(", Angular Speed = ");
// Serial.println(lift.liftMotor.getVelocity());
times[i/10] = time;
inEff[i/10] = i;
outEff[i/10] = applEffort;
vel[i/10] = lift.liftMotor.getVelocity();
delay(100);
}

lift.liftMotor.setEffort(-200);
while(digitalRead(1) == 1){
// Serial.println("Going down!");
}
lift.liftMotor.setEffort(0);
Serial.println("Times:");
for(int i2 = 0; i2 < 41; i2++){
Serial.println(times[i2]);
}
Serial.println("Inputs:");
for(int i2 = 0; i2 < 41; i2++){
Serial.println(inEff[i2]);
}
Serial.println("Applied:");
for(int i2 = 0; i2 < 41; i2++){
Serial.println(outEff[i2]);
}
Serial.println("Speed:");
for(int i2 = 0; i2 < 41; i2++){
Serial.println(vel[i2]);
}
>>>>>>> Stashed changes

/**/

delay(1);
};


