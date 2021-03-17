#include <fourbar.h>
#include <gripper.h>

const float DEPOT = 0;
const float PREP25 = 3.225;
const float PLACE25 = 3.425;
const float DIST25 = 5;

enum armState{idle, movingArm, movingGripper};


class Arm{
    private:
    
    
    int prevState;
    public:
    int state;
    fourBar lift;
    gripper gripper;
    


    float gripperPos;
    float liftPos;

    void runArm();
    void setAngle(float angle);
    void setGripperState(bool open);
    void pause();
    void resume();

};