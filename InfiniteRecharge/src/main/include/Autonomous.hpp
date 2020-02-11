#pragma once

#include <Drive.hpp>

class AutoManager { 
    private:
    DriveManager *driveManager;
    bool testToggle = true;

    public:
    AutoManager(DriveManager *drive);
    void testAuto();
};