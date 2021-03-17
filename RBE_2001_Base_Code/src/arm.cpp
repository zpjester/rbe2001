#include <arm.h>
void Arm::runArm(){
    if(state == movingGripper && armTimer.isExpired()){
        state = idle;
    }

    if(state == idle){}
    else if(state == armPaused){}
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
        Gripper.open();
    }   
    else{
        Gripper.close();
    }
    armTimer.reset(750);
    state = movingGripper;
}
void Arm::pause(){
    prevState = state;
    state = armPaused;
    lift.pause();   
}
void Arm::resume(){
    state = prevState;
    lift.resume();
}