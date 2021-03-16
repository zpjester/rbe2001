#/*include <Arduino.h>
#include <Romi32U4.h>
// #include <Timer.h> //unused
#include "PIDController.cpp"
class driveBase{
    private:
        double gearRatio;
        int encoderRes;
        double wheelDiam;
        double wheelBase;
        Romi32U4Motors motors;
        Romi32U4Encoders encoders;
        int missedCommands;
    public:
        //constructor
        driveBase(){
            gearRatio = 120;
            encoderRes = 12;
            wheelDiam = 2.75;//inches
            wheelBase = 5.5;//inches            
        }

        void encReset(){
            int temp;
            temp = encoders.getCountsAndResetLeft();
            temp = encoders.getCountsAndResetRight();
        }
        //Get angular position of a wheel
        double getWheelAngle(String side){
            if(side.equals("LEFT")){
                return (encoders.getCountsLeft() / (encoderRes * gearRatio)) * 360;
            }
            else if(side.equals("RIGHT")){
                return (encoders.getCountsRight() / (encoderRes * gearRatio)) * 360;
            }
            else if(side.equals("AVERAGE")){
                return ((encoders.getCountsLeft() / (encoderRes * gearRatio) + encoders.getCountsRight() / (encoderRes * gearRatio)) / 2)* 360;
            }
            else{
                return 0;
            }
        }
        double getWheelDistance(String side){
            return (getWheelAngle(side)) * PI / 180 * (wheelDiam / 2);
        }
        
        void tankDrive(double leftThrottle, double rightThrottle){
            int maxThrottle = 300;
            motors.setEfforts(leftThrottle * maxThrottle, rightThrottle * maxThrottle);
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
        void directionalDrive(String direction, double throttle){
            if(!direction.equals("NO INPUT")){
                missedCommands = 0;
            }
            else{
                missedCommands++;
            }
            if(missedCommands < 200){
                //can't use switch here since it is a string
                if(direction.equals("FORWARDS") || direction.equals("NORTH")){
                    arcadeDrive(throttle, 0);
                    
                }
                else if(direction.equals("RIGHT") || direction.equals("EAST")){
                    arcadeDrive(0, throttle);
                }
                else if(direction.equals("BACKWARDS") || direction.equals("SOUTH")){
                    arcadeDrive(-throttle, 0);
                }
                else if(direction.equals("LEFT") || direction.equals("WEST")){
                    arcadeDrive(0, -throttle);
                }
                else if(direction.equals("NORTHEAST")){
                    arcadeDrive(throttle, throttle);
                }
                else if(direction.equals("SOUTHEAST")){
                    arcadeDrive(-throttle, throttle);
                }
                else if(direction.equals("SOUTHWEST")){
                    arcadeDrive(-throttle, -throttle);
                }
                else if(direction.equals("NORTHWEST")){
                    arcadeDrive(throttle, -throttle);
                }
                else if(direction.equals("STOP")){
                    arcadeDrive(0, 0);
                }

            }
            else{
                missedCommands = 0;
                arcadeDrive(0, 0);
            }
            
            
        }
        /*
        void driveWheelsDistance(double leftDistance, double rightDistance){//CANNOT turn with 1 wheel stationary. PID needs tuning
            if(leftDistance == 0 || rightDistance == 0){
                Serial.println("Error: driveWheelsDistance() requires both distances to be nonzero");
            }
            else{
                PIDController steerPID();
                steerPID.setPID(0.05, 0, 0)
                double avgDistance = (abs(leftDistance) + abs(rightDistance)) / 2;
                double standardThrottle = 0.5;
                double leftCompletion = 0;
                double rightCompletion = 0;
                double endingFudge = 0.01;//end within 1% of target
                double leftBaseThrottle = leftDistance / avgDistance;
                double rightBaseThrottle = rightDistance / avgDistance;
                int steps;
                double decelDistance = 3;
                double minThrottle = 0.25;
                double decelModifier;
                steerPID.init(0, 0);
                encReset();
                while(leftCompletion < 1 - endingFudge || rightCompletion < 1 - endingFudge){
                    steps++;
                    double leftCompletedDist = getWheelDistance("LEFT");
                    double rightCompletedDist = getWheelDistance("RIGHT");
                    leftCompletion = leftCompletedDist / leftDistance;
                    rightCompletion = rightCompletedDist / rightDistance;
                    double avgCompletion = (leftCompletion + rightCompletion) / 2;
                    double avgCompletedDist = avgCompletion * avgDistance;
                    double completionDeltaFrac = leftCompletion - rightCompletion;
                    double completionDelta = completionDeltaFrac * avgDistance;
                    steerPID.runPID(completionDelta, 0);
                    double adjFactor = steerPID.getPID();
                    double leftThrottle = (abs(leftBaseThrottle) - adjFactor) * (abs(leftBaseThrottle) / leftBaseThrottle);
                    double rightThrottle = (abs(rightBaseThrottle) + adjFactor) * (abs(rightBaseThrottle) / rightBaseThrottle);
                    
                    double targetDistance = avgDistance - avgCompletedDist;
                    if(targetDistance < decelDistance){
                        decelModifier = minThrottle + (1 - minThrottle) * (targetDistance / decelDistance);
                    }
                    else{
                        decelModifier = 1;
                    }
                    leftThrottle *= decelModifier;
                    rightThrottle *= decelModifier;

                    leftThrottle *= standardThrottle;
                    rightThrottle *= standardThrottle;
                    tankDrive(leftThrottle, rightThrottle);
                    Serial.print("Steps run: ");
                    Serial.print(steps);
                    Serial.print(" Left distance driven: ");
                    Serial.print(leftCompletedDist);
                    Serial.print(" Right completed distance: ");
                    Serial.println(rightCompletedDist);
                }
                tankDrive(0, 0);
            }
        }
        void driveDistance(double dist){
            driveWheelsDistance(dist, dist);
        }
        void turnAngle(double angle){
            double wheelDist = angle / 360 * PI * wheelBase;
            driveWheelsDistance(wheelDist, -wheelDist);
        }
        

};
*/