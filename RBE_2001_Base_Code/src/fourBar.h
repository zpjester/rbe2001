#include <blueMotor.h>
class fourBar{
private:
blueMotor liftMotor;

float targetHeight;

const float torqueRatio =  30;
const float pivotHeight = 4.8;//inches, height of powered crank
const float crankLength = 3;//inches

public:
bool runArm();//Go to target position, return true if finished
void goToAngle(float angle);//Set target position
float getAngle();
void setup();
void reset();

};