#include <fourbar.h>
#include <gripper.h>
#include <Timer.h>
const float DEPOT = 0.025;
const float IDLECARRY = 0.3;
const float DEPOTDIST = 7;
const float PREP25 = 3.325;
const float PLACE25 = 3.5;
const float DIST25 = 5.5;
const float PREP45 = 3.0;
const float PLACE45 = 1.6;
const float DIST45 = 16;

const float DEPOTINTER = 27.94;
const float ROOFINTER = 29.21;

const float TRAVERSEDIST = 30;//INCHES

enum armState{idle, movingArm, movingGripper, armPaused};
/*
start,
    collectLift, moveToWall, roofGrab, oldLift,//Grab old panel
    oldToInt, oldLower, oldTurnToDepot, oldMoveToDepot, oldLowerToDepot oldDrop,//Place old panel
    newGrab, newToInt, newTurnToRoof, newToPrep, newPlace, newRelease,//grab / place new panel
    emptyToInt, traverseTurn1, traverseDriveToStart, 
    traverseTurn2, traverseCross, traverseTurn3, traverseToInt, traverseTurn4,//traverse
    completed
    */

class Arm{
    private:
    Timer armTimer = Timer(750);
    
    int prevState;
    public:
    int state;
    fourBar lift;
    gripper Gripper;
    


    float gripperPos;
    float liftPos;

    void runArm();
    void setAngle(float angle);
    void setGripperState(bool open);
    void pause();
    void resume();

};