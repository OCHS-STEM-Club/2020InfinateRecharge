#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>
#include <AHRS.h>

#define TURN_K -0.3

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

    public:
    DriveManager();
    void drive();
    void subclassTurn(double turnValue, double moveValue);
    bool autoDrive(double distance);
    void autoDrivePrep();

}; 