#pragma once //runs only once

#include <frc/WPILib.h> 
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h> 

class ShooterManager { 
    private:
    WPI_TalonFX *shootMotor;

    WPI_TalonSRX *feederMotor;
    WPI_TalonSRX *hoodMotor;

    frc::XboxController *xbox;

    frc::DigitalInput *hoodEncoder;
    
    double velocityOut;
    double velocityAct;
    bool currentEncoderState;
    int hoodEncoderCount = 0;

    public:
    ShooterManager();
    void shoot(double velocityWant, double enabled);
    void hoodRotate(double hoodPosition);
    void shootTest();

};
