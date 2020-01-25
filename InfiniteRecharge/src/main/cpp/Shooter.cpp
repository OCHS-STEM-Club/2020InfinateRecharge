#include <Shooter.hpp>

ShooterManager::ShooterManager () {
    shootMotor = new rev::CANSparkMax(9, rev::CANSparkMax::MotorType::kBrushless);
    shootMotor->GetEncoder().SetPosition(0);

    pidController = new rev::CANPIDController(*shootMotor);
    pidController->SetP(0);
    pidController->SetI(0);
    pidController->SetD(0);
    //pidController->SetIZone(0);
    //pidController->SetFF(0);
    pidController->SetOutputRange(1,-1);
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
}