#include "driveBaseV2.h"
driveBaseV2::driveBaseV2(){
    active = false;
    driveMode = stopped;
    baseWidth = 5.625;
    wheelDiam = 2.7375;
    gearRatio = 120;
    encoderRes = 12;
    L_Target_Dist = 0;
    R_Target_Dist = 0;
    L_Position = 0;
    R_Position = 0;
    max_Throttle = 300;
}
extern Romi32U4Motors driveMotors;
extern Romi32U4Encoders driveEncoders;
extern PIDController steerPID;
extern Timer driveTimer;
void tankDrive(double L_Throttle, double R_Throttle){
    
}