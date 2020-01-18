#pragma once //Runs code below once

#include <frc/WPILib.h>
#include <networktables/NetworkTable.h> //Allows us to get get data from Network Table
#include <networktables/NetworkTableInstance.h>

#include <Drive.hpp>

#define AREA_DISTANCE_RATIO 4.1823379 //2.11249
#define MAX_STEER 0.3 // the maximum value sent to steer the robot
#define STEER_K 0.05

class VisionManager { //Creates vision manager object
private: //Only the vision subclass can effect
frc::Joystick *stick;

bool imageToggle = true; //bool = true or false
bool imageSwitch = true;

double rawDistance; //double = any number
double distanceFlat;

double turnOutput;

DriveManager *driveManager;

public: //Everything below is made accessable
    VisionManager();
    void display();
    void distance();
    void trackTurn();
};