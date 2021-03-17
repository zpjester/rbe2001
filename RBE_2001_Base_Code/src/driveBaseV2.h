#include <Romi32U4.h>
#include <PIDController.h>
#include <Timer.h>
#include <utils.h>

enum driveModes{stopped, encoders, proximity};
class driveBaseV2{
    private:
    PIDController steerPID;
    PIDController proxPID;
    Romi32U4Motors driveMotors;
    Romi32U4Encoders driveEncoders;
    // PIDController steerPID;
    Timer driveTimer();
    bool handleDistDrive();
    bool handlePIDDrive();
    bool handleUltrasonicDrive();
    void startPIDDrive(float l_dist, float r_dist, float throttle);
    public:

    int active = false;
    
    int driveMode = stopped;
    int prevMode = stopped;
    
    float L_Target_Dist = 0;
    float R_Target_Dist = 0;
    float L_Position = 0;
    float R_Position = 0;
    float max_Throttle = 300;
    float distTolerance = .0625;
    float l_throttle = 0;
    float r_throttle = 0;

    float trim = 1.0;


    float getLeftDist();
    float getRightDist();
    void resetEncoders();
    void runDrive();
    void stopDrive();
    void pauseDrive();
    void resumeDrive();
    void tankDrive(float L_Throttle, float R_Throttle);
    void arcadeDrive(float yAxis, float xAxis);
    void driveDist(float left_dist, float right_dist, float throttle);
    void driveDistPID(float left_dist, float right_dist, float throttle);
    void turnAngle(float angle, float throttle);
    void turnAnglePID(float angle, float throttle);
    void driveUltrasonic(float targetCM);
    driveBaseV2();
};