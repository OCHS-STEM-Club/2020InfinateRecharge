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