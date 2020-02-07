#include <Autonomous.hpp>

AutoManager::AutoManager (DriveManager *drive) {
    this->driveManager = drive;
}

void AutoManager::testAuto() {
    if(testToggle){
        this->driveManager->autoPrep();
        testToggle = false;
    }
    this->driveManager->autoDrive(4);
}