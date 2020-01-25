#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>

class ShooterManager { 
    private:
    rev::CANSparkMax *shootMotor;
    rev::CANPIDController *pidController;
    
    double velocityOut;
    double velocityAct;

    public:
    ShooterManager();
    void shoot(double velocityWant, double enabled);
};
