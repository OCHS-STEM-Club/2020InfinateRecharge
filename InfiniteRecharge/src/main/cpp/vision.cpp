#include <vision.hpp>

VisionManager::VisionManager () {
stick = new frc::Joystick{0};

driveManager = new DriveManager();

}

void VisionManager::display() {
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

  table->PutNumber("pipeline", 1);
  frc::SmartDashboard::PutBoolean("has target", table->GetNumber("tv", 0.0));

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

  /*frc::SmartDashboard::PutNumber("tx", targetOffsetAngle_Horizontal);
  frc::SmartDashboard::PutNumber("ty", targetOffsetAngle_Vertical);
  frc::SmartDashboard::PutNumber("ta", targetArea);
  frc::SmartDashboard::PutNumber("ts", targetSkew);*/

  //rawDistance = targetArea * AREADISTANCERATIO;
  rawDistance = (targetArea * -1.31) +12.8;
  frc::SmartDashboard::PutNumber("raw distance", rawDistance);
  //distanceFlat = sqrt(pow(rawDistance, 2) - pow(8.1875,2));
  //frc::SmartDashboard::PutNumber("target distance", distanceFlat);

}

double clamp(double in,double minval,double maxval) {
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

void VisionManager::trackTurn() {
  std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  double targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0);
  double targetOffsetAngle_Vertical = table->GetNumber("ty",0.0);
  double targetArea = table->GetNumber("ta",0.0);
  double targetSkew = table->GetNumber("ts",0.0);
  double tv = table->GetNumber("tv",0.0);

  if (tv == 1) {
    turnOutput = targetOffsetAngle_Horizontal * STEER_K; //or divid by max value (27 degrees)
    turnOutput = clamp(turnOutput,-MAX_STEER,MAX_STEER);
    driveManager->subclassTurn(turnOutput);
  }
  else {
    driveManager->subclassTurn(0);
  }
}