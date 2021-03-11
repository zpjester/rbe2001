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