#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h> 

class ShooterManager { 
    private:
    rev::CANSparkMax *shootMotor;
    rev::CANPIDController *pidController;

    WPI_TalonSRX *feederMotor;

    frc::XboxController *xbox;
    
    double velocityOut;
    double velocityAct;

    public:
    ShooterManager();
    void shoot(double velocityWant, double enabled);
    void shootTest();
};
