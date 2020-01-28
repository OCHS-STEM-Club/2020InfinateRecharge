#include <Drive.hpp>

DriveManager::DriveManager () {
  driveMotorLeft = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
  driveMotorRight = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);

  slaveMotorLeft1 = new rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushless);
  slaveMotorLeft2 = new rev::CANSparkMax(5, rev::CANSparkMax::MotorType::kBrushless);
  slaveMotorRight1 = new rev::CANSparkMax(6, rev::CANSparkMax::MotorType::kBrushless);
  slaveMotorRight2 = new rev::CANSparkMax(7, rev::CANSparkMax::MotorType::kBrushless);

  slaveMotorLeft1->Follow(*driveMotorLeft, false); //follows drive motor left
  slaveMotorLeft2->Follow(*driveMotorLeft, false);
  slaveMotorRight1->Follow(*driveMotorRight, false);
  slaveMotorRight2->Follow(*driveMotorRight, false);

  driveMotorLeft->SetSmartCurrentLimit(60); //sets max current limit
  driveMotorRight->SetSmartCurrentLimit(60); //defalt is 80
  slaveMotorLeft1->SetSmartCurrentLimit(60);
  slaveMotorLeft2->SetSmartCurrentLimit(60);
  slaveMotorRight1->SetSmartCurrentLimit(60);
  slaveMotorRight2->SetSmartCurrentLimit(60); 

  /*leftDriveEnc = new rev::CANEncoder(*driveMotorLeft); //creates encoder object
  rightDriveEnc = new rev::CANEncoder(*driveMotorRight);
  leftDriveEnc->SetPosition(0); //sets encoder object to 0
  rightDriveEnc->SetPosition(0);*/
  driveMotorLeft->GetEncoder().SetPosition(0);
  driveMotorRight->GetEncoder().SetPosition(0);

  robotDrive = new frc::DifferentialDrive(*driveMotorLeft, *driveMotorRight); //object holds motor cont info and does alc for that
  stick = new frc::Joystick{0};

  try{
		gyro = new AHRS(SPI::Port::kMXP);
	}
	catch(std::exception ex){
		std::string err_string = "Error initalizing navX-MXP: ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}
	gyro->Reset();
}

double absDouble (double x) { //method that takes a varible and gets the absolute value of it
  if (x < 0) {
    return -x;
  }
  else {
    return x;
  }
}

int Sign(double input) { //method that returns numbers for its relation to 0
    if (input > 0) {
        return 1;
    }
    else if (input < 0) {
        return -1;
    }
    else if (input == 0) {
        return 0;
    }
}

double deadband(double joystickValue, double deadbandValue) { //colins special proportioanl deadband thingy just copy
    if(absDouble(joystickValue) < 0.2){
        return 0;
    }
    else{
        return (1 / (1 - deadbandValue)) * (joystickValue + (-Sign(joystickValue) * deadbandValue));
    } 
}

void DriveManager::drive() {
    xStickValue = -deadband(stick->GetRawAxis(1), 0.2); //getting raw axis values
    yStickValue = deadband(stick->GetRawAxis(2), 0.2);

    robotDrive->ArcadeDrive(xStickValue, yStickValue);

    frc::SmartDashboard::PutNumber("left encoder", driveMotorLeft->GetEncoder().GetPosition()); //getting motor controller data and putting it on smart dashboard
    frc::SmartDashboard::PutNumber("right encoder", driveMotorLeft->GetEncoder().GetPosition());
    frc::SmartDashboard::PutNumber("left velocity", driveMotorLeft->GetEncoder().GetVelocity());
    frc::SmartDashboard::PutNumber("right velocity", driveMotorLeft->GetEncoder().GetVelocity());

    frc::SmartDashboard::PutNumber("left current", driveMotorLeft->GetOutputCurrent());
    frc::SmartDashboard::PutNumber("right current", driveMotorRight->GetOutputCurrent());
}

void DriveManager::subclassTurn(double turnValue, double moveValue) { //allows different subclass to access drive system to turn robot (Ex vision tracking turns robot)
    robotDrive->ArcadeDrive(moveValue, turnValue);
}

double distanceToRev(double in){
    in *= 12;
    in /= 18.84;
    in *= 7.18;
    return in;
}

double clampDrive(double in,double minval,double maxval) {
  if (in > maxval) {
    return maxval;
  }
  else if (in < minval) {
    return minval;
  }
  else {
    return in;
  }
}

void DriveManager::autoDrivePrep() {
  leftEncLast = driveMotorLeft->GetEncoder().GetPosition();
  rightEncLast = driveMotorRight->GetEncoder().GetPosition();
  gyroLast = gyro->GetAngle();
}

bool DriveManager::autoDrive(double distance){
  leftCurrentPos = driveMotorLeft->GetEncoder().GetPosition() - leftEncLast;
  rightCurrentPos = driveMotorRight->GetEncoder().GetPosition() - rightEncLast;
  revNeed = distanceToRev(distance);

  leftOffset = revNeed - leftCurrentPos;
  rightOffset = revNeed - rightCurrentPos;
  avgOffset = (rightOffset + leftOffset)/2.0;

  power = avgOffset / (revNeed / 2);
  power = clampDrive(power,-0.5,0.5);
  turnCorrection = (gyro->GetAngle() - gyroLast) * TURN_K;
  robotDrive->ArcadeDrive(power, turnCorrection);

  if (avgOffset < 2){
    return true;    
  }
  else {
    return false;
  }
}


