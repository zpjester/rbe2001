#include <Romi32U4.h>
#include "PIDController.cpp"
#include <Timer.h>
#include <utils.h>
class driveBaseV2{
    private:
        
    Romi32U4Motors driveMotors;
    Romi32U4Encoders driveEncoders;
    PIDController steerPID();
    Timer driveTimer();
    bool handleDistDrive();
    bool handlePIDDrive();
    public:
    float getLeftDist();
    float getRightDist();
    void resetEncoders();
    bool runDrive();
    void stopDrive();
    void pauseDrive();
    void resumeDrive();
    void tankDrive(double L_Throttle, double R_Throttle);
    void arcadeDrive(double yAxis, double xAxis);
    void driveDist(double left_dist, double right_dist, float throttle);
    void driveDistPID(double left_dist, double right_dist, float throttle);
    void turnAngle(double angle, float throttle);
    void turnAnglePID(double angle, float throttle);
    driveBaseV2();
};