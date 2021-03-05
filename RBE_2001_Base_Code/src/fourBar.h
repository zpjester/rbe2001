#include <blueMotor.h>
class fourBar{
private:
blueMotor liftMotor;

float targetHeight;

const float gearRatio;
const float pivotHeight;//inches, height of powered crank
const float crankLength;//inches

public:
bool runArm();//Go to target position, return true if finished
void goToHeight(float height);//Set target position


};