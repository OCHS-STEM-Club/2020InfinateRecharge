#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>

class DriveManager { 
    private:
    rev::CANSparkMax *driveMotorLeft; // declares motor controllers
    rev::CANSparkMax *driveMotorRight;

    rev::CANSparkMax *slaveMotorLeft1;
    rev::CANSparkMax *slaveMotorLeft2;
    rev::CANSparkMax *slaveMotorRight1;
    rev::CANSparkMax *slaveMotorRight2;

    rev::CANEncoder *leftDriveEnc;
    rev::CANEncoder *rightDriveEnc;

    frc::DifferentialDrive *robotDrive;
    frc::Joystick *stick;

    double xStickValue; //creates stick varibles
    double yStickValue;
    public:
    DriveManager();
    void drive();
    void subclassTurn(double turnValue, double moveValue);
}; 








































//BOOL