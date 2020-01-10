#pragma once

#include <frc/WPILib.h>
//#include <Robot.h>
#include <ctre/Phoenix.h> 
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

class ColorManager {
 private:
  rev::ColorSensorV3 m_colorSensor{frc::I2C::Port::kOnboard};
  rev::ColorMatch m_colorMatcher;
  static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

    frc::Joystick *stick;
    WPI_TalonSRX *spinMotor;

    double xStickValue;

 public:
    ColorManager();
    void manualSpin();
    void colorFinder();
};