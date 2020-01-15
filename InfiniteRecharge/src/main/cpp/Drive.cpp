#include <Drive.hpp>

DriveManager::DriveManager () {
    driveMotorLeft = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
    driveMotorRight = new rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushless);

    slaveMotorLeft1 = new rev::CANSparkMax(5, rev::CANSparkMax::MotorType::kBrushless);
    slaveMotorLeft2 = new rev::CANSparkMax(6, rev::CANSparkMax::MotorType::kBrushless);
    slaveMotorRight1 = new rev::CANSparkMax(7, rev::CANSparkMax::MotorType::kBrushless);
    slaveMotorRight2 = new rev::CANSparkMax(8, rev::CANSparkMax::MotorType::kBrushless);

    slaveMotorLeft1->Follow(*driveMotorLeft, false);
    slaveMotorLeft2->Follow(*driveMotorLeft, false);
    slaveMotorRight1->Follow(*driveMotorRight, false);
    slaveMotorRight2->Follow(*driveMotorRight, false);

    leftDriveEnc = new rev::CANEncoder(*driveMotorLeft);
    rightDriveEnc = new rev::CANEncoder(*driveMotorRight);
    leftDriveEnc->SetPosition(0);
    rightDriveEnc->SetPosition(0);

    robotDrive = new frc::DifferentialDrive(*driveMotorLeft, *driveMotorRight);
    stick = new frc::Joystick{0};
}

void DriveManager::drive() {
    xStickValue = stick->GetRawAxis(1);
    yStickValue = stick->GetRawAxis(2);

    robotDrive->ArcadeDrive(xStickValue, yStickValue);

    frc::SmartDashboard::PutNumber("left encoder", leftDriveEnc->GetPosition());
    frc::SmartDashboard::PutNumber("right encoder", rightDriveEnc->GetPosition());
}