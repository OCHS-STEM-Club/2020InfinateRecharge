#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>
#include <AHRS.h>

#define TURN_K -0.5

class DriveManager { 
    private:
    rev::CANSparkMax *driveMotorLeft; // declares motor controllers
    rev::CANSparkMax *driveMotorRight;

    rev::CANSparkMax *slaveMotorLeft1;
    rev::CANSparkMax *slaveMotorLeft2;
    rev::CANSparkMax *slaveMotorRight1;
    rev::CANSparkMax *slaveMotorRight2;

    //rev::CANEncoder *leftDriveEnc;
    //rev::CANEncoder *rightDriveEnc;

    frc::DifferentialDrive *robotDrive;
    frc::Joystick *stick;
    frc::XboxController *xbox;

    AHRS *gyro;

    double xStickValue; //creates stick varibles
    double yStickValue;

    double revNeed;
    double leftOffset;
    double rightOffset;
    double avgOffset;
    double leftCurrentPos;
    double rightCurrentPos;
    double power;
    double leftEncLast;
    double rightEncLast;
    double gyroLast;
    double turnCorrection;

    double currentAngle;

    bool colorwheelExtended = false;
    bool b = true;

    public:
    DriveManager();
    void drive();
    void subclassTurn(double turnValue, double moveValue);
    bool autoDrive(double distance);
    void autoPrep();
    void autoTurn(double angle);
}; 