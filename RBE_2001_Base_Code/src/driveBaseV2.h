#include <Romi32U4.h>
#include "PIDController.cpp"
#include <Timer.h>
#include <utils.h>
class driveBaseV2{
    private:
    PIDController steerPID;
    Romi32U4Motors driveMotors;
    Romi32U4Encoders driveEncoders;
    // PIDController steerPID;
    Timer driveTimer();
    bool handleDistDrive();
    bool handlePIDDrive();
    void startPIDDrive(float l_dist, float r_dist, float throttle);
    public:
    float getLeftDist();
    float getRightDist();
    void resetEncoders();
    bool runDrive();
    void stopDrive();
    void pauseDrive();
    void resumeDrive();
    void tankDrive(float L_Throttle, float R_Throttle);
    void arcadeDrive(float yAxis, float xAxis);
    void driveDist(float left_dist, float right_dist, float throttle);
    void driveDistPID(float left_dist, float right_dist, float throttle);
    void turnAngle(float angle, float throttle);
    void turnAnglePID(float angle, float throttle);
    driveBaseV2();
};