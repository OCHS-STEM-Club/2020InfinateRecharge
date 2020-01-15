#include <vision.hpp>

VisionManager::VisionManager () {
stick = new frc::Joystick{0};
}

void VisionManager::track() {
std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
  double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
  double targetArea = table->GetNumber("ta",0.0);
  double targetSkew = table->GetNumber("ts",0.0);

  frc::SmartDashboard::PutNumber("tx", targetOffsetAngle_Horizontal);
  frc::SmartDashboard::PutNumber("ty", targetOffsetAngle_Vertical);
  frc::SmartDashboard::PutNumber("ta", targetArea);
  frc::SmartDashboard::PutNumber("ts", targetSkew);

  if (stick->GetRawButton(4) && imageToggle) {
    imageSwitch = !imageSwitch;
    imageToggle = false;
  }
  else if (!stick->GetRawButton(4)) {
    imageToggle = true;
  }

  if (imageSwitch) {
    table->PutNumber("camMode", 0);
    table->PutNumber("ledMode", 3);
  }
  else {
    table->PutNumber("camMode", 1);
    table->PutNumber("ledMode", 1);
  }

  if (abs(targetOffsetAngle_Horizontal) < 1 && abs(targetOffsetAngle_Vertical) < 1) {
    frc::SmartDashboard::PutBoolean("is alligned", true);
  }
  else {
    frc::SmartDashboard::PutBoolean("is alligned", false);

    if (targetOffsetAngle_Vertical > 0) {
        frc::SmartDashboard::PutString("vert correction", "up");
    }
    else {
        frc::SmartDashboard::PutString("vert correction", "down");
    }

    if (targetOffsetAngle_Horizontal > 0) {
        frc::SmartDashboard::PutString("horizontal correction", "right");
    }
    else {
        frc::SmartDashboard::PutString("horizontal correction", "left");
    }
  }
  
}

void VisionManager::distance() {
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
  double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
  double targetArea = table->GetNumber("ta",0.0);
  double targetSkew = table->GetNumber("ts",0.0);

  frc::SmartDashboard::PutNumber("tx", targetOffsetAngle_Horizontal);
  frc::SmartDashboard::PutNumber("ty", targetOffsetAngle_Vertical);
  frc::SmartDashboard::PutNumber("ta", targetArea);
  frc::SmartDashboard::PutNumber("ts", targetSkew);

  //rawDistance = targetArea * AREADISTANCERATIO;
  rawDistance = (targetArea * -1.31) +12.8;
  frc::SmartDashboard::PutNumber("raw distance", rawDistance);
  //distanceFlat = sqrt(pow(rawDistance, 2) - pow(8.1875,2));
  //frc::SmartDashboard::PutNumber("target distance", distanceFlat);
}