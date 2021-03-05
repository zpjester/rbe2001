#include <servo32u4.h>
class gripper{
    private:
    float currAngle;//Current angle
    float targetAngle;//Set angle
    float minAnglePot;//Potentiometer reading at 0 deg
    float maxAnglePot;//Potentiometer reading 1y 180 deg

    float openAngle;//Open position
    float closedAngle;//Closed position
    public:
    void setAngle(float angle);
    void open();
    void closed();
    float getAngle();
    bool runServo();
};