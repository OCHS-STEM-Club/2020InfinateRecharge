#include <Climber.hpp>

ClimbManager::ClimbManager () {
    climbMotor = new WPI_TalonFX(15);
    climbMotor->GetSensorCollection().SetIntegratedSensorPosition(0,10);
    climbMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
    //climbMotor->SetSensorPhase(true);
	//climbMotor->SetInverted(false);
	climbMotor->ConfigAllowableClosedloopError(0, 0, 10);
	climbMotor->Config_kP(0, 0, 10);
	climbMotor->Config_kI(0, 0, 10);
	climbMotor->Config_kD(0, 0, 10);

    xbox = new frc::XboxController{1};
}

void ClimbManager::climb() {
    pov = xbox->GetPOV();
    if (pov == 0){
        climbMotor->Set(ControlMode::Position, 0); 
    }
    else if (pov == 180){
        climbMotor->Set(ControlMode::Position, 0); 
    }

    //climbMotor->Set(ControlMode::PercentOutput, xbox->GetRawAxis(5));
}  
