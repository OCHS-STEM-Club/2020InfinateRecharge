#pragma once //runs only once

#include <frc/WPILib.h> 
#include <ctre/Phoenix.h>

class ClimbManager { 
    private:
    WPI_TalonFX *climbMotor;
    frc::XboxController *xbox;
    int pov;
    public:
    ClimbManager();
    void climb();
};