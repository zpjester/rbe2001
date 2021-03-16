
#include <gripper.h>
int position = 0;
Servo32U4 servo;
bool Open = true;

void Gripper::init(){
    servo.Init();
    servo.Attach();
    servo.Write(openVal);
}

void Gripper::open(){
    servo.Write(openVal);
    Open = true;
    Serial.println(Open);
}

void Gripper::close(){
    servo.Write(closedVal);
    Open = false;
    Serial.println(Open);
}

int Gripper::getPosition(){
    return position;
}

void Gripper::toggle(){
    if(Open) close();
    else open();
}