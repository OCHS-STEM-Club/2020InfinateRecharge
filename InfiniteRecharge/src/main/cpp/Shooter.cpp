#include <Shooter.hpp>

ShooterManager::ShooterManager () {
    shootMotor = new WPI_TalonFX(12);
    shootMotor->GetSensorCollection().SetIntegratedSensorPosition(0,10);
    shootMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    //shootMotor->SetSensorPhase(true);
	//shootMotor->SetInverted(false);
	shootMotor->ConfigAllowableClosedloopError(0, 0, 10);
	shootMotor->Config_kP(0, 0, 10);
	shootMotor->Config_kI(0, 0, 10);
	shootMotor->Config_kD(0, 0, 10);

    hoodMotor = new WPI_TalonSRX(14);

    feederMotor = new WPI_TalonSRX(13);
    xbox = new frc::XboxController{1};
    hoodEncoder = new frc::DigitalInput(1);
    currentEncoderState = hoodEncoder->Get();
}

void ShooterManager::shoot(double velocityWant, double enabled) {
    velocityAct = shootMotor->GetSensorCollection().GetIntegratedSensorVelocity();
    frc::SmartDashboard::PutNumber("shooter rpm", velocityAct);

    if (enabled) {
        shootMotor->Set(ControlMode::Velocity, velocityWant); //replace 0 with correct
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

void ShooterManager::hoodRotate(double hoodPosition){
    if (currentEncoderState != hoodEncoder->Get()){
        if (hoodMotor->Get() > 0){
            hoodEncoderCount++;
        }
        else {
            hoodEncoderCount--;
        }
        currentEncoderState = hoodEncoder->Get();
    }
    
}
