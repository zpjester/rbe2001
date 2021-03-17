#include <gripper.h>
 extern Servo32U4 servo;

bool Open = true;

void gripper::init(){
    servo.Init();
    servo.Attach();

    openVal = openAngle / totalAngle * (maxSignal - minSignal) + minSignal;
    closedVal = closedAngle / totalAngle * (maxSignal - minSignal) + minSignal;
    
    servo.Write(openVal);
}

void gripper::open(){
    servo.Write(openVal);
    Open = true;
    Serial.println(Open);
}

void gripper::close(){
    servo.Write(closedVal);
    Open = false;
    Serial.println(Open);
}

// int gripper::getAngle(){
//     return position;
// }

