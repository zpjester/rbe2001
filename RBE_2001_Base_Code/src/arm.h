#include <fourbar.h>
#include <gripper.h>
#include <Timer.h>
const float DEPOT = 0.125;
const float IDLECARRY = 0.125;
const float DEPOTDIST = 10;
const float PREP25 = 3.325;
const float PLACE25 = 3.625;
const float DIST25 = 6.5;
const float DIST25PICKUP = 7;
const float PREP45 = 3.0;
const float PLACE45 = 1.59;
const float DIST45 = 13;
const float DIST45PICKUP = 15;

const float DEPOTINTER = 27.94;
const float ROOFINTER = 33;

const float TRAVERSEDIST = 32;//INCHES

enum armState{idle, movingArm, movingGripper, armPaused};
/*
    zinitialize, start,
    collectLift, moveToWall, roofGrab, oldLift,//Grab old panel
    oldToInt, oldLower, oldTurnToDepot, oldSquareAtDepot, oldLowerToDepot oldDrop,//Place old panel
    waitForNew, newGrab, newLift, newToInt, newTurnToRoof, newToPrep, newToRoof, newPlace, newAdjLeft, newAdjRight, newAdjReturn, newPullBack, newRelease,//grab / place new panel
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