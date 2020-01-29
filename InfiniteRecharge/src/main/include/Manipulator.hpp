#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h> 
#include <rev/CANSparkMax.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

#define COLORWHEELRATIO 0.25 //4/16

class ManipulatorManager {
 private:
  rev::ColorSensorV3 m_colorSensor{frc::I2C::Port::kOnboard};
  rev::ColorMatch m_colorMatcher;
  /*static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113); */

  static constexpr frc::Color kBlueTarget = frc::Color(0.251, 0.473, 0.276);
  static constexpr frc::Color kGreenTarget = frc::Color(0.297, 0.545, 0.158);
  static constexpr frc::Color kRedTarget = frc::Color(0.616, 0.318, 0.067);
  static constexpr frc::Color kYellowTarget = frc::Color(0.446, 0.480, 0.074);

  frc::Joystick *stick;
  frc::XboxController *xbox;

  WPI_TalonSRX *spinMotor;
  WPI_TalonSRX *trapDoorMotor;
  
  rev::CANSparkMax *intakeRotateMotor;
  WPI_TalonSRX *intakeSpinMotor;

  frc::Servo *linActuator;

  rev::CANPIDController *intakePidController;

  double xStickValue;
  std::string gameData;
  std::string currentColor;
  int colorCount;

  double encStartRot;
  double encEndRot;
  double currentEncRot;
  
  bool intakeButtonToggle = true;
  int rotateControlMode = 0;
    

 public:
    ManipulatorManager();
    void manualColorSpin();
    void colorFinder();
    void countSpins();
    void countSpinsEnc();
    void intake();
    void linearActuator();
    void intakeTest();
};