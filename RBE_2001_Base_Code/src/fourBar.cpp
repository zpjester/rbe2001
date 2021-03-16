#include <fourBar.h>
extern blueMotor liftMotor;
bool runArm(){
    return liftMotor.runMotor();
}
void goToAngle(float angle){
    liftMotor.moveToAngle(angle * 30);
}