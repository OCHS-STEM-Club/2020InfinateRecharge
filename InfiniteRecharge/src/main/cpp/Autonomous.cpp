#include <Autonomous.hpp>
#include <Robot.h>

AutoManager::AutoManager (DriveManager *drive, ManipulatorManager *manipulator) {
    this->driveManager = drive;
    this->manipulatorManager = manipulator;
}

void AutoManager::testAuto() {
    switch(autoStep) {
        case 0:
            this->manipulatorManager->intakeStartup();
            break;
        case 1:
            this->driveManager->autoPrep();
            break;
        case 2:
            this->driveManager->autoBasic();
            break;
    }
    frc::SmartDashboard::PutNumber("auto step", autoStep);
}

void AutoManager::lowDeposit() {
    frc::SmartDashboard::PutNumber("auto step", autoStep);
    switch (autoStep) {
        case 0:
            this->driveManager->autoPrep();
            break;
        case 1:
            this->driveManager->autoDrive(7);
            break;
        case 2:
            this->manipulatorManager->intakeAutoHeight(false);
            break;
        case 3:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAutoStart();
            break;
        case 4:
            this->manipulatorManager->intakeAutoHeight(true);
            this->manipulatorManager->intakeAuto(2);
            break;
        case 5:
            this->manipulatorManager->intakeAutoHeight(true);
            this->driveManager->autoPrep();
            break;
        case 6:
            this->driveManager->autoDrive(-2);
            this->manipulatorManager->intakeAutoHeight(true);
            break;
        case 7:
            this->manipulatorManager->intakeStartup();
            break;
    }
}