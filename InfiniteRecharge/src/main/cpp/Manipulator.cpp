#include <Manipulator.hpp>

ManipulatorManager::ManipulatorManager () {
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);

    stick = new frc::Joystick{0};
    spinMotor = new WPI_TalonSRX(8);
    spinMotor->GetSensorCollection().SetQuadraturePosition(0, 10);
    currentColor = " ";
    colorCount = 0;
    encStartRot = 0;
}

/*int Sign(double input) {
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

double deadband(double joystickValue, double deadbandValue) {
    if(abs(joystickValue) < 0.2){
        return 0;
    }
    else{
        return (1 / (1 - deadbandValue)) * (joystickValue + (-Sign(joystickValue) * deadbandValue));
    } 
}*/

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
  if (stick->GetRawButton(9)){
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