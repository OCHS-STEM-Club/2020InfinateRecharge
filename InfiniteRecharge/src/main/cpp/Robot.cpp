/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream> //Includes a prepopulated iostream include

#include <frc/smartdashboard/SmartDashboard.h>


Robot::Robot() {
  //manipulatorManager = new ManipulatorManager();
  driveManager = new DriveManager();
  //visionManager = new VisionManager();
  //shooterManager = new ShooterManager();
  //climbManager = new ClimbManager();
  //autoManager = new AutoManager(driveManager);
}  

frc::Joystick *stick; //Initialzing the joystick
frc::XboxController *xbox;

double visionMove;
double visionTurn;
double visionRPM;

bool intakeRotateStart = true;
bool intakeRotateStartCompleted = false;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  stick = new frc::Joystick{0}; //Assigning the joystick to USB port 0 on the driver station
  xbox = new frc::XboxController{1};

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }

  driveManager->autoPrep();
}
bool a =false;
void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }

  /*if (! intakeRotateStartCompleted) {
    manipulatorManager->intakeStartup();
  } */
  if (!a) {
  a = driveManager->autoDrive(1);
  }
}

void Robot::TeleopInit() {} //Initalize Teleop

void Robot::TeleopPeriodic() {
  
 /* if (xbox->GetRawButton(7)) {
    manipulatorManager->colorFinder();
  }
  else if (xbox->GetRawButton(8)) {
    manipulatorManager->countSpins();
  }
  //else if (stick->GetRawButton(8)){
  //  manipulatorManager->countSpinsEnc();
  //}
  else {
    manipulatorManager->manualColorSpin();
  }

  visionManager->display(); //runs vision manager once teleop starts
  //visionManager->distance(); //runs vision manager once teleop starts
  
  if (!stick->GetRawButton(12)) {
		driveManager->drive();//0, 0, false);
    shooterManager->shoot(0, false);
	}
	else {
		visionTurn = visionManager->trackTurn();
    visionMove = visionManager->trackMove();
    //visionRPM = ?;

    //driveManager->driveTrain(visionMove, visionTurn, true);
    driveManager->subclassTurn(visionTurn, visionMove);
    //shooterManager->shoot(visionRPM, true);
	}*/
  
  driveManager->drive();
  //manipulatorManager->intakeTest();
  //shooterManager->shootTest();
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
