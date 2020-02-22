#pragma once

#include <Drive.hpp>
#include <Manipulator.hpp>

class AutoManager { 
    private:
    DriveManager *driveManager;
    ManipulatorManager *manipulatorManager;

    public:
    AutoManager(DriveManager *drive, ManipulatorManager *manipulator);
    void testAuto();
    void lowDeposit();
};