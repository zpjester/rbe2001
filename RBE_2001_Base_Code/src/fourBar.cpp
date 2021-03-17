#include <fourBar.h>

void fourBar::goToAngle(float angle){
    fourBar::liftMotor.moveToAngle(angle * torqueRatio);
}

bool fourBar::runArm(){
    return fourBar::liftMotor.runMotor();
}

void fourBar::setup(){
    fourBar::liftMotor.setup();
}
void fourBar::reset(){
    fourBar::liftMotor.reset();
}
float fourBar::getAngle(){
    return fourBar::liftMotor.getRadians() / torqueRatio;
}
void fourBar::goDown(){
    // Serial.println("Resetting Arm");
    pinMode(1, INPUT_PULLUP);
    fourBar::liftMotor.setEffort(-300);
    while(digitalRead(1) == 1){
        delay(1);
        // Serial.println(digitalRead(1));
    }
    fourBar::liftMotor.setEffort(300);
    delay(40);
    
    fourBar::liftMotor.setEffort(0);

    fourBar::liftMotor.reset();
    // Serial.println(fourBar::liftMotor.getPosition());
    delay(1000);
}

void fourBar::pause(){
    fourBar::liftMotor.setEffort(0);
}
void fourBar::resume(){}