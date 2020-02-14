#pragma once //runs only once

#include <frc/WPILib.h> 
#include <ctre/Phoenix.h>

class ClimbManager { 
    private:
    WPI_TalonFX *climbMotor;
    frc::XboxController *xbox;
    //frc::XboxController *driveXbox;
    //frc::Joystick *stick;
    int pov;
    public:
    ClimbManager();
    void climb();
    void climbTest();
};