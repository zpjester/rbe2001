#include "driveBaseV2.h"

    int active = false;
    enum modes{stopped, direct, distance, PID, paused};
    int driveMode = stopped;
    int prevMode = stopped;
    const float baseWidth = 5.625;
    const float wheelDiam = 2.7375;
    const int gearRatio = 120;
    const int encoderRes = 12;
    float L_Target_Dist = 0;
    float R_Target_Dist = 0;
    float L_Position = 0;
    float R_Position = 0;
    float max_Throttle = 300;
    float distTolerance = .125;
    float l_throttle = 0;
    float r_throttle = 0;

extern Romi32U4Motors driveMotors;
extern Romi32U4Encoders driveEncoders;
extern PIDController steerPID;
extern Timer driveTimer;
float getLeftDist(){
    float counts = driveEncoders.getCountsLeft();
    float dist = counts / (encoderRes * gearRatio) * PI * wheelDiam;
    return dist;
}
float getRightDist(){
    float counts = driveEncoders.getCountsRight();
    float dist = counts / (encoderRes * gearRatio) * PI * wheelDiam;
    return dist; 
}
void resetEncoders(){
    driveEncoders.getCountsAndResetLeft();
    driveEncoders.getCountsAndResetRight();
}


void tankDrive(float L_Throttle, float R_Throttle){
    driveMode = direct;
    driveMotors.setEfforts(L_Throttle * max_Throttle, R_Throttle * max_Throttle);
}
void arcadeDrive(double throttle, double steering){//Throttle / steering from -1 to 1, mix is similar to axes on an analog stick. Math based on WPILib for FRC
            //Quadrant-based system
            int quadrant;
            double rightThrottle;
            double leftThrottle;
            if(throttle >= 0){
                if(steering >= 0){
                    quadrant = 1;
                }
                else{
                    quadrant = 2;
                }
            }
            else{
                if(steering >= 0){
                    quadrant = 4;
                }
                else{
                    quadrant = 3;
                }
            }

            
            double maxInput;
            if(abs(throttle) > abs(steering)){
                maxInput = throttle;
            }
            else{
                if(throttle != 0){
                    maxInput = abs(steering) * throttle / abs(throttle);
                }
                else{
                    maxInput = abs(steering);
                }                    
            }
            switch(quadrant){
                case 1:
                leftThrottle = maxInput;
                rightThrottle = throttle - steering;
                break;
                case 2:
                leftThrottle = throttle + steering;
                rightThrottle = maxInput;
                break;
                case 3:
                leftThrottle = maxInput;
                rightThrottle = throttle - steering;
                break;
                case 4:
                leftThrottle = throttle + steering;
                rightThrottle = maxInput;
                break;                
            }
            
            tankDrive(leftThrottle, rightThrottle);
        };

void driveDist(float left_dist, float right_dist, float throttle){
    L_Target_Dist = left_dist;
    R_Target_Dist = right_dist;
    L_Position = 0;
    R_Position = 0;
    resetEncoders();
    float avg_dist = (abs(left_dist) + abs(right_dist)) / 2;
    l_throttle = left_dist / avg_dist * throttle;
    r_throttle = right_dist / avg_dist * throttle;
    float maxThrottle = max(l_throttle, r_throttle);
    if(maxThrottle > 1){
        l_throttle /= maxThrottle;
        r_throttle /= maxThrottle;
    }
    tankDrive(l_throttle, r_throttle);
    driveMode = distance;
}
void turnAngle(float angle, float throttle){
    float dist = angle * PI / 180 * baseWidth / 2;
    L_Target_Dist = -dist;
    R_Target_Dist = dist;
    L_Position = 0;
    R_Position = 0;
    resetEncoders();
    l_throttle = throttle * sign(L_Target_Dist);
    r_throttle = throttle * sign(R_Target_Dist);
    float maxThrottle = max(l_throttle, r_throttle);
    if(maxThrottle > 1){
        l_throttle /= maxThrottle;
        r_throttle /= maxThrottle;
    }
    tankDrive(l_throttle, r_throttle);
    driveMode = distance;
}



void stopDrive(){
    tankDrive(0, 0);
    driveMode = stopped;
}

bool handleDistDrive(){
    L_Position = getLeftDist();
    R_Position = getRightDist();
    bool L_Complete = (abs(L_Target_Dist - L_Position) <= distTolerance);
    bool R_Complete = (abs(R_Target_Dist - R_Position) <= distTolerance);
    if(L_Complete && R_Complete){
        stopDrive();
        return true;
    }
    else{
        if(L_Complete){
            l_throttle = 0;
        }
        if(R_Complete){
            r_throttle = 0;
        }
        tankDrive(l_throttle, r_throttle);
        driveMode = distance;
        return false;
    }
}
bool handlePIDDrive(){
    return false;
}


bool runDrive(){
    switch (driveMode){
        case stopped:
        return true;
        break;
        case direct:
        return true;
        break;
        case distance:
        return handleDistDrive();
        break;
        case PID:
        return handlePIDDrive();
        break;
        case paused:
        return true;
        break;
        default:
        return false;
        break;
    }
}

void pauseDrive(){
    prevMode = driveMode;
    tankDrive(0, 0);
    driveMode = paused;
}
void resumeDrive(){
    tankDrive(l_throttle, r_throttle);
    driveMode = prevMode;
}