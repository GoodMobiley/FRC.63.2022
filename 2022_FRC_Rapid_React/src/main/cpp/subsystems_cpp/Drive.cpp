#include "subsystems/Drive.h"

#include <frc/smartdashboard/SmartDashboard.h>

RapidReactDrive::RapidReactDrive()
{
    m_drive.SetSafetyEnabled(false);

    m_frontRight.SetInverted(true);
    m_rearRight.SetInverted(true);

    m_drive.SetMaxOutput(1);
    m_drive.SetExpiration(units::time::second_t(24));
    m_drive.SetDeadband(0.001);
    m_drive.FeedWatchdog();
}

void RapidReactDrive::Periodic(){

}

void RapidReactDrive::SimulationPeriodic(){

}

void RapidReactDrive::iterate(frc::XboxController &pilot){
        
    m_drive.DriveCartesian(
        pow(-pilot.GetLeftY(), 3), 
        pow(pilot.GetLeftX(), 3), 
        pow(pilot.GetRightX(), 3), 
        0
    );
}