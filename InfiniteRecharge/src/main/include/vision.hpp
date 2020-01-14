#pragma once

#include <frc/WPILib.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
//#include <math.h>

#define AREADISTANCERATIO 4.1823379 //2.11249

class VisionManager {
private:
frc::Joystick *stick;

bool imageToggle = true;
bool imageSwitch = true;

double rawDistance;
double distanceFlat;

public:
    VisionManager();
    void track();
    void distance();
};