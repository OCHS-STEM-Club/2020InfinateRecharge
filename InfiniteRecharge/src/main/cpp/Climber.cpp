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

    //stick = new frc::Joystick {0};
    xbox = new frc::XboxController{1};
    //driveXbox = new frc::XboxController{2};
}

void ClimbManager::climb() {
    pov = xbox->GetPOV();
    //pov = driveXbox->GetPOV();
    if (pov == 0){
        climbMotor->Set(ControlMode::Position, 0); 
    }
    else if (pov == 180){
        climbMotor->Set(ControlMode::Position, 0); 
    }

   /* if (stick->GetRawButton(7)) {
        climbMotor->Set(ControlMode::Position, 0); 
    }
    else if (stick->GetRawButton(8)) {
        climbMotor->Set(ControlMode::Position, 0); 
    }*/

    //climbMotor->Set(ControlMode::PercentOutput, xbox->GetRawAxis(5));
}  

void ClimbManager::climbTest() {
    climbMotor->Set(ControlMode::PercentOutput, xbox->GetRawAxis(5));
}
