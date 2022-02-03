#include "subsystems/Drive.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <fmt/core.h>

using namespace std;

RapidReactDrive::RapidReactDrive()
{
    m_drive.SetDeadband(.02);

    m_frontLeft.SetInverted(false);
    m_rearLeft.SetInverted(false);
    m_frontRight.SetInverted(true);
    m_rearRight.SetInverted(true);
}

void RapidReactDrive::Config(){

    TalonRef talons[] = 
    {
        m_frontLeft,
        m_rearLeft,
        m_frontRight,
        m_rearRight
    };

    for(TalonRef talon : talons)
        {
            talon.ref.ConfigNominalOutputForward(0.0, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.ConfigNominalOutputReverse(0.0, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.ConfigPeakOutputForward(1.0, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.ConfigPeakOutputReverse(-1.0, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.EnableVoltageCompensation(true);
            talon.ref.ConfigVoltageCompSaturation(11.5, RobotMap::CAN_TIME_OUT_MS);

            talon.ref.Config_kP(0, 0.375, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.Config_kI(0, 0.0, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.Config_kD(0, 0.0, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.Config_kF(0, 0.35, RobotMap::CAN_TIME_OUT_MS);

            talon.ref.SelectProfileSlot(0, 0);
            talon.ref.ConfigClosedLoopPeakOutput(0, 1.0, RobotMap::CAN_TIME_OUT_MS);

            //sets sensor to mag encoder
            talon.ref.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, RobotMap::CAN_TIME_OUT_MS);
            talon.ref.ConfigSelectedFeedbackCoefficient(1.0, 0, RobotMap::CAN_TIME_OUT_MS);

            talon.ref.SetSelectedSensorPosition(0);
        }
}

void RapidReactDrive::printEncoders(){
    TalonRef talons[] = 
    {
        m_frontLeft,
        m_rearLeft,
        m_frontRight,
        m_rearRight
    };

    for(TalonRef talon : talons)
    {
        fmt::print(
            "Talon ID: " + to_string(talon.ref.GetBaseID()) + "\n" +
            "Sensor Pos: " + to_string(talon.ref.GetSelectedSensorPosition()) + "\n" +
            "Sensor Vel: " + to_string(talon.ref.GetSelectedSensorVelocity()) + "\n"
        );
    }
}

void RapidReactDrive::Periodic(){

}

void RapidReactDrive::SimulationPeriodic(){

}

void RapidReactDrive::iterate(frc::XboxController& pilot){
    m_drive.DriveCartesian(
        pow(-pilot.GetLeftY(), 1), 
        pow(pilot.GetLeftX(), 1), 
        pow(pilot.GetRightX(), 1),
        0
    );
}