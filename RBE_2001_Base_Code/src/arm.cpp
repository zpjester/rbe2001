#include <arm.h>
void Arm::runArm(){
    if(state == idle){}
    else if(state == movingArm){
        bool complete = lift.runArm();
        if(complete){
            state = idle;
        }
    }
}
void Arm::setAngle(float angle){
    lift.goToAngle(angle);
    state = movingArm;
}
void Arm::setGripperState(bool open){
    if(open){
        gripper.open();
    }   
    else{
        gripper.close();
    }
}
void Arm::pause(){
    prevState = state;
    state = idle;
    lift.pause();   
}
void Arm::resume(){
    state = prevState;
    lift.resume();
}