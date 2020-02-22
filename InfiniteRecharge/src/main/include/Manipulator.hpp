#pragma once

#include <frc/WPILib.h>
#include <ctre/Phoenix.h> 
#include <rev/CANSparkMax.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

#define COLORWHEELRATIO 0.25 //4/16
#define LOW_GOAL_HEIGHT 7.2

class ManipulatorManager {
private:
    rev::ColorSensorV3 m_colorSensor{frc::I2C::Port::kOnboard};
    rev::ColorMatch m_colorMatcher;
    /*static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113); */

    static constexpr frc::Color kBlueTarget = frc::Color(0.375, 0.438, 0.188);
    static constexpr frc::Color kGreenTarget = frc::Color(0.429, 0.429, 0.143);
    static constexpr frc::Color kRedTarget = frc::Color(0.599, 0.319, 0.079);
    static constexpr frc::Color kYellowTarget = frc::Color(0.512, 0.415, 0.073);

    frc::Joystick *stick;
    frc::XboxController *xbox;

    WPI_TalonSRX *spinMotor;

    rev::CANSparkMax *intakeRotateMotor;
    WPI_TalonSRX *intakeSpinMotor;

    frc::Servo *linActuator;

    rev::CANPIDController *intakePidController;

    frc::Timer *timerM;

    double xStickValue;
    std::string gameData;
    std::string currentColor;
    int colorCount;

    double encStartRot;
    double encEndRot;
    double currentEncRot;

    bool intakeButtonToggle = true;
    int rotateControlMode = 0;
    double rotatePosition;

 public:
    ManipulatorManager();
    void manualColorSpin();
    void colorFinder();
    void countSpins();
    void stopWheel();
    //void countSpinsEnc();
    void intake();
    void linearActuator();
    void intakeTest();
    void intakeStartup();
    void intakeAuto(double duration);
    void intakeAutoStart();
    void intakeAutoHeight(bool sustainHeight);
};