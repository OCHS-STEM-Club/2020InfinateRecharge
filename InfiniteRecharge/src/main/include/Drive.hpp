#pragma once

#include <frc/WPILib.h>
#include <rev/CANSparkMax.h>

class DriveManager {
    private:
    //rev::CANSparkMax *driveMotorLeft;
    //rev::CANSparkMax *driveMotorRight;
    public:
    DriveManager();
    void drive();
}; 