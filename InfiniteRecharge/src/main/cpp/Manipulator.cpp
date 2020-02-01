#include <Manipulator.hpp>

ManipulatorManager::ManipulatorManager () {
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);

  stick = new frc::Joystick{0};
  xbox = new frc::XboxController{1};

  spinMotor = new WPI_TalonSRX(8);
  spinMotor->GetSensorCollection().SetQuadraturePosition(0, 10);

  trapDoorMotor = new WPI_TalonSRX(9);
  trapDoorMotor->GetSensorCollection().SetQuadraturePosition(0, 10);

  intakeRotateMotor = new rev::CANSparkMax(10, rev::CANSparkMax::MotorType::kBrushless);
  intakeSpinMotor = new WPI_TalonSRX(11);

  currentColor = " ";
  colorCount = 0;
  encStartRot = 0;

  linActuator = new frc::Servo(9);
  linActuator->SetBounds(2.0, 1.8, 1.0, 1.2, 1.0);

  intakePidController = new rev::CANPIDController(*intakeRotateMotor);
  intakePidController->SetP(0);
  intakePidController->SetI(0);
  intakePidController->SetD(0);
  //intakePidController->SetIZone(0);
  //intakePidController->SetFF(0);
  intakePidController->SetOutputRange(1,-1);

  trapDoorMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
  //trapDoorMotor->SetSensorPhase(true);
	//trapDoorMotor->SetInverted(false);
	trapDoorMotor->ConfigAllowableClosedloopError(0, 0, 10);
	trapDoorMotor->Config_kP(0, 0, 10);
	trapDoorMotor->Config_kI(0, 0, 10);
	trapDoorMotor->Config_kD(0, 0, 10);
}

double absDoubleM (double x) { //method that takes a varible and gets the absolute value of it
  if (x < 0) {
    return -x;
  }
  else {
    return x;
  }
}

int SignM(double input) {
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

double deadbandM(double joystickValue, double deadbandValue) {
    if(absDoubleM(joystickValue) < 0.1){
        return 0;
    }
    else{
        return (1 / (1 - deadbandValue)) * (joystickValue + (-SignM(joystickValue) * deadbandValue));
    } 
}

void ManipulatorManager::manualColorSpin() {
    xStickValue = stick->GetRawAxis(1);
    //xStickValue = deadband(xStickValue,0.5);

    spinMotor->Set(xStickValue);
    frc::SmartDashboard::PutNumber("spin motor roations", spinMotor->GetSensorCollection().GetQuadraturePosition() / 4096.0);


    frc::Color detectedColor = m_colorSensor.GetColor();

  /**
   * Run the color match algorithm on our detected color
   */
  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  if (matchedColor == kBlueTarget) {
    colorString = "Blue";
  } else if (matchedColor == kRedTarget) {
    colorString = "Red";
  } else if (matchedColor == kGreenTarget) {
    colorString = "Green";
  } else if (matchedColor == kYellowTarget) {
    colorString = "Yellow";
  } else {
    colorString = "Unknown";
  }

  /**
   * Open Smart Dashboard or Shuffleboard to see the color detected by the 
   * sensor.
   */
  frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
  frc::SmartDashboard::PutNumber("Confidence", confidence);
  frc::SmartDashboard::PutString("Detected Color", colorString);
}

void ManipulatorManager::colorFinder() {
  gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

  frc::Color detectedColor = m_colorSensor.GetColor();

  /**
   * Run the color match algorithm on our detected color
   */
  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  if (matchedColor == kBlueTarget) {
    colorString = "B";
  } else if (matchedColor == kRedTarget) {
    colorString = "R";
  } else if (matchedColor == kGreenTarget) {
    colorString = "G";
  } else if (matchedColor == kYellowTarget) {
    colorString = "Y";
  } else {
    colorString = "Unknown";
  }

  frc::SmartDashboard::PutString("Detected Color", colorString);

  if (colorString != gameData) {
    spinMotor->Set(0.2);
  }
  else {
    spinMotor->Set(0);
  }
  
}

void ManipulatorManager::countSpins() {

  frc::Color detectedColor = m_colorSensor.GetColor();

  /**
   * Run the color match algorithm on our detected color
   */
  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  if (matchedColor == kBlueTarget) {
    colorString = "B";
  } else if (matchedColor == kRedTarget) {
    colorString = "R";
  } else if (matchedColor == kGreenTarget) {
    colorString = "G";
  } else if (matchedColor == kYellowTarget) {
    colorString = "Y";
  } else {
    colorString = "Unknown";
  }

  if (currentColor != colorString) {
    currentColor = colorString;
    if (currentColor == "Y") {
      colorCount++;
    }
  }

  if (stick->GetRawButton(10)) {
    colorCount = 0;
  }

  if (colorCount < 7) {
    spinMotor->Set(0.4);
  }
  else {
    spinMotor->Set(0);
  }

  frc::SmartDashboard::PutString("Detected Color", colorString);
}

void ManipulatorManager::countSpinsEnc(){
  currentEncRot = spinMotor->GetSensorCollection().GetQuadraturePosition() / 4096.0;
  frc::SmartDashboard::PutNumber("spin motor roations", currentEncRot);

  if (stick->GetRawButton(9)){ //sets start and end values
    encStartRot = currentEncRot;
    encEndRot = encStartRot + (3.5 * (1/COLORWHEELRATIO));
  }

  if (currentEncRot < encEndRot){
    spinMotor->Set(-0.2);
  }
  else {
    spinMotor->Set(0);
  }
}

void ManipulatorManager::intake() {
  //intakeSpinMotor->Set(deadbandM(xbox->GetRawAxis(1), 0.2));
  if (xbox->GetRawButton(1)) {
    intakeSpinMotor->Set(0.3);
  }
  else if (xbox->GetRawButton(2)) {
    intakeSpinMotor->Set(-0.3);
  }

  if (xbox->GetRawButton(3) && intakeButtonToggle) {
    rotateControlMode = 1;
    intakePidController->SetReference(0, rev::ControlType::kPosition);
  }
  else if (xbox->GetRawButton(4) && intakeButtonToggle) {
    //intakePidController->SetReference(0, rev::ControlType::kPosition);
    //intakeRotateMotor->StopMotor();
    rotateControlMode = 2;
  }
  else {
    intakeButtonToggle = true;
  }
  
  if (rotateControlMode == 2) {
    if (intakeRotateMotor->GetEncoder().GetPosition() > 0) { //replace 0 with desired location
      intakeRotateMotor->Set(-0.2);
    }
    else {
      intakeRotateMotor->Set(0);
    }
  }
  if (rotateControlMode == 3) {
    intakeRotateMotor->Set(deadbandM(xbox->GetRawAxis(5), 0.2));
  }

  if (xbox->GetRawButton(11)) { //fix button
    trapDoorMotor->Set(ControlMode::Position, 0); //replace 0 with correct
  }
  if (xbox->GetRawButton(12)) { //fix button
    trapDoorMotor->Set(ControlMode::Position, 0); //replace 0 with correct
  }
}

void ManipulatorManager::linearActuator() {
    if (stick->GetRawButton(9)) {
    //linActuator->SetSpeed(1);
    linActuator->SetPosition(1);
  }
  else if (stick->GetRawButton(10)) {
    //linActuator->SetSpeed(-1);
    linActuator->SetPosition(2);
  }
  /*else {
    //linActuator->SetSpeed(0);
    //linActuator->SetDisabled();
  }*/
}

void ManipulatorManager::intakeTest() {
  intakeSpinMotor->Set(deadbandM(xbox->GetRawAxis(1), 0.2));
  intakeRotateMotor->Set(deadbandM(xbox->GetRawAxis(5), 0.2));

  if (xbox->GetRawButton(1)) {
    trapDoorMotor->Set(0.2);
  }
  else if (xbox->GetRawButton(2)) {
    trapDoorMotor->Set(-0.2);
  }
  else {
    trapDoorMotor->Set(0);
  }
}