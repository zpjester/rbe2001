#include <driveBaseV2.h>
#include <Ultrasonic.h>
    extern Ultrasonic US;
const float baseWidth = 5.625;
    const float wheelDiam = 2.7375;
    const int gearRatio = 120;
    const int encoderRes = 12;
extern Romi32U4Motors driveMotors;
extern Romi32U4Encoders driveEncoders;
extern PIDController steerPID;
extern Timer driveTimer;
float driveBaseV2::getLeftDist(){
    float counts = driveEncoders.getCountsLeft();
    float dist = counts / (encoderRes * gearRatio) * PI * wheelDiam;
    return -dist;
}
float driveBaseV2::getRightDist(){
    float counts = driveEncoders.getCountsRight();
    float dist = counts / (encoderRes * gearRatio) * PI * wheelDiam;
    return -dist; 
}
void driveBaseV2::resetEncoders(){
    driveEncoders.getCountsAndResetLeft();
    driveEncoders.getCountsAndResetRight();
}


void driveBaseV2::tankDrive(float L_Throttle, float R_Throttle){
    driveMotors.setEfforts(-L_Throttle * max_Throttle, -R_Throttle * max_Throttle);
}
void driveBaseV2::arcadeDrive(float throttle, float steering){//Throttle / steering from -1 to 1, mix is similar to axes on an analog stick. Math based on WPILib for FRC
            //Quadrant-based system
            int quadrant;
            float rightThrottle;
            float leftThrottle;
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

            
            float maxInput;
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
            
            driveBaseV2::tankDrive(leftThrottle, rightThrottle);
        };

void driveBaseV2::driveDist(float left_dist, float right_dist, float throttle){
    L_Target_Dist = left_dist;
    R_Target_Dist = right_dist;
    L_Position = 0;
    R_Position = 0;
    driveBaseV2::resetEncoders();
    float avg_dist = (abs(left_dist) + abs(right_dist)) / 2;
    l_throttle = left_dist / avg_dist * throttle;
    r_throttle = right_dist / avg_dist * throttle;
    float maxThrottle = max(l_throttle, r_throttle);
    if(maxThrottle > 1){
        l_throttle /= maxThrottle;
        r_throttle /= maxThrottle;
    }
    driveBaseV2::tankDrive(l_throttle, r_throttle);
    driveMode = encoders;
    L_Complete = false;
    R_Complete = false;
}
void driveBaseV2::turnAngle(float angle, float throttle){
    float dist = angle * PI / 180 * baseWidth / 2;
    L_Target_Dist = -dist;
    R_Target_Dist = dist;
    L_Position = 0;
    R_Position = 0;
    driveBaseV2::resetEncoders();
    l_throttle = throttle * sign(L_Target_Dist);
    r_throttle = throttle * sign(R_Target_Dist);
    float maxThrottle = max(l_throttle, r_throttle);
    if(maxThrottle > 1){
        l_throttle /= maxThrottle;
        r_throttle /= maxThrottle;
    }
    l_throttle *= 0.75;
    r_throttle *= 0.75;
    driveBaseV2::tankDrive(l_throttle, r_throttle);
    driveMode = encoders;
    L_Complete = false;
    R_Complete = false;
}

void driveBaseV2::driveUltrasonic(float targetCM){
    L_Target_Dist = targetCM;
    driveMode = proximity;
    proxPID.setPID(.02, -0.00025, 1);
    proxPID.init(US.getDistanceCM(), targetCM);
    resetEncoders();
}


bool driveBaseV2::handleUltrasonicDrive(){
    if(abs(US.getDistanceCM() - L_Target_Dist) < .375){
        stopDrive();
        return true;
    }
    else{
        proxPID.runPID(US.getDistanceCM(), L_Target_Dist);
        float throttle = proxPID.getPID();
        if(abs(throttle) > 1){
            throttle = sign(throttle);
        }
        throttle *= .4;

        L_Position = driveBaseV2::getLeftDist();
        R_Position = driveBaseV2::getRightDist();
        
        float LRDifference = L_Position - R_Position;
        const float KP = 1;
        float L_ThrottleOut = throttle * (1 - LRDifference * sign(throttle) * KP);
        float R_ThrottleOut = throttle * (1 + LRDifference * sign(throttle) * KP);

        tankDrive(L_ThrottleOut * trim, R_ThrottleOut / trim);
        driveMode = proximity;
        return false;
    }
}
void driveBaseV2::stopDrive(){
    driveBaseV2::tankDrive(0, 0);
    driveMode = stopped;
}

bool driveBaseV2::handleDistDrive(){
    const float startScaleDist = 4;//inches
    const float endThrottleFraction = 0.375;
    L_Position = driveBaseV2::getLeftDist();
    R_Position = driveBaseV2::getRightDist();
    float L_Remaining = abs(L_Target_Dist - L_Position);
    float R_Remaining = abs(R_Target_Dist - R_Position);
    float LRDifference = L_Position - R_Position;
    const float KP = .4;
    float L_ThrottleOut = l_throttle * (1 - LRDifference * sign(l_throttle) * KP);
    float R_ThrottleOut = r_throttle * (1 + LRDifference * sign(r_throttle) * KP);
    if(!L_Complete){
        L_Complete = (L_Remaining <= distTolerance);
    }
    if(!R_Complete){
        R_Complete = (R_Remaining <= distTolerance);
    }     
    if(abs(max(L_ThrottleOut, R_ThrottleOut) > 1)){
        L_ThrottleOut /= abs(max(L_ThrottleOut, R_ThrottleOut));
        R_ThrottleOut /= abs(max(L_ThrottleOut, R_ThrottleOut));
    }
    if(L_Complete && R_Complete){
        driveBaseV2::stopDrive();
        Serial.println("Drive Complete");
        return true;
    }
    else{
        if(L_Complete){
            l_throttle = 0;
            L_ThrottleOut = 0;
        }
        if(R_Complete){
            r_throttle = 0;
            R_ThrottleOut = 0;
        }
        float l_adj_throttle = L_ThrottleOut;
        float r_adj_throttle = R_ThrottleOut;
        if(L_Remaining < startScaleDist){
            l_adj_throttle = l_throttle * abs((abs((L_Remaining / startScaleDist)) + (abs(startScaleDist - L_Remaining) * endThrottleFraction)));
        }
        if(R_Remaining < startScaleDist){
            r_adj_throttle = r_throttle * abs((abs(R_Remaining / startScaleDist) + (abs(startScaleDist - R_Remaining) * endThrottleFraction)));
        }

        driveBaseV2::tankDrive(l_adj_throttle, r_adj_throttle);
        driveMode = encoders;
        Serial.println((L_Remaining + R_Remaining) / 2);
        return false;
    }
}
bool driveBaseV2::handlePIDDrive(){
    return false;
}


void driveBaseV2::runDrive(){
    bool complete;
    switch (driveMode){
        case stopped:
        tankDrive(0, 0);
        break;
        case encoders:
        complete = handleDistDrive();
        if(complete){
            driveMode = stopped;
        }
        break;
        case proximity:
        complete = handleUltrasonicDrive();
        if(complete){
            driveMode = stopped;
        }
        break;
        case dTimer:
        complete = handleTimeDrive();
        if(complete){
            driveMode = stopped;
        }
        break;
        case paused:
        tankDrive(0, 0);
        break;
        default:
        driveMode = stopped;
        break;
    }
}

void driveBaseV2::pauseDrive(){
    prevMode = driveMode;
    driveBaseV2::tankDrive(0, 0);
    driveMode = paused;
}
void driveBaseV2::resumeDrive(){
    driveBaseV2::tankDrive(l_throttle, r_throttle);
    driveMode = prevMode;
}
driveBaseV2::driveBaseV2(){
    // steerPID.setPID(0, 0, 0);
}

void driveBaseV2::startPIDDrive(float l_dist, float r_dist, float throttle){
    
}

void driveBaseV2::driveTime(float dThrottle, int driveTime){
    l_throttle = dThrottle;
    r_throttle = dThrottle;
    endTime = millis() + driveTime;
    driveMode = dTimer;
}

bool driveBaseV2::handleTimeDrive(){
    if(millis() >= endTime){
        // if(false){
        stopDrive();
        driveMode = stopped;
        return true;
    }
    else{
        tankDrive(l_throttle, r_throttle);
        driveMode = dTimer;
        return false;
    }
}