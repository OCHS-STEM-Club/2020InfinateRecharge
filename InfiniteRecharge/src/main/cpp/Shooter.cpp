#include <Shooter.hpp>

ShooterManager::ShooterManager () {
    shootMotor = new rev::CANSparkMax(12, rev::CANSparkMax::MotorType::kBrushless);
    shootMotor->GetEncoder().SetPosition(0);

    pidController = new rev::CANPIDController(*shootMotor);
    pidController->SetP(0);
    pidController->SetI(0);
    pidController->SetD(0);
    //pidController->SetIZone(0);
    //pidController->SetFF(0);
    pidController->SetOutputRange(1,-1);

    feederMotor = new WPI_TalonSRX(13);
    xbox = new frc::XboxController{1};
}

void ShooterManager::shoot(double velocityWant, double enabled) {
    velocityAct = shootMotor->GetEncoder().GetPosition();
    frc::SmartDashboard::PutNumber("shooter rpm", velocityAct);

    if (enabled) {
        pidController->SetReference(velocityWant, rev::ControlType::kVelocity);
    }
    else {
        shootMotor->Set(0);
    }

    if ((velocityAct - velocityWant) < 20 && xbox->GetRawButton(12) ) { //fix button later and allowable error
        feederMotor->Set(0.2);
    }
    /*else if (xbox->GetRawButton(12)) { //fix button later
        feederMotor->Set(0.2);
    }*/
    else {
        feederMotor->Set(0); 
    }
}

void ShooterManager::shootTest() { //warning use only by its self
    shootMotor->Set(xbox->GetRawAxis(5));
    
    if (xbox->GetRawButton(12)) { //fix button later
        feederMotor->Set(0.2);
    }
}
