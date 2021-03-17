#include <servo32u4.h>
class gripper{
    private:
    Servo32U4 servo;
    float currAngle;//Current angle
    float targetAngle;//Set angle
    const float minAnglePot = 0;//Potentiometer reading at 0 deg
    const float maxAnglePot = 1024;//Potentiometer reading at 180 deg

    const float openAngle = 5;//Open position
    const float closedAngle = 100;//Closed position
    const int minSignal = 900;
    const int maxSignal = 2100;
    const float totalAngle = 120;
    int openVal;
    int closedVal;
    public:
    void init();
    void setAngle(float angle);
    void open();
    void close();
    float getAngle();
    bool runServo();
};