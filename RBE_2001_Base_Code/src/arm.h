#include <fourbar.h>
#include <gripper.h>


class arm{
    private:
    enum armState{idle, movingArm, movingGripper};
    int state;
    int prevState;
    fourBar lift;
    Gripper gripper;
    float gripperPos;
    float liftPos;

    void runArm();
    void setHeight(double height);
    void setGripperState(bool open);
    void pause();
    void resume();
    void goToGround();
};