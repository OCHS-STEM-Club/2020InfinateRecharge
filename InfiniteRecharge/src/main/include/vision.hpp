#pragma once

#include <frc/WPILib.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

#include <Drive.hpp>

#define AREA_DISTANCE_RATIO 4.1823379 //2.11249
#define MAX_STEER 0.3 // the maximum value sent to steer the robot
#define STEER_K 0.05

class VisionManager {
private:
frc::Joystick *stick;

bool imageToggle = true;
bool imageSwitch = true;

double rawDistance;
double distanceFlat;

double turnOutput;

DriveManager *driveManager;

public:
    VisionManager();
    void display();
    void distance();
    void trackTurn();
};