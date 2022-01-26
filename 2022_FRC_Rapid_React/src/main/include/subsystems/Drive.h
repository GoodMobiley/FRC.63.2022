#pragma once

#include "RobotMap.h"

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/XboxController.h>

class RapidReactDrive: public frc2::SubsystemBase {
    public:
        RapidReactDrive();
        void Config();
        void printEncoders();
        void Periodic() override;
        void SimulationPeriodic() override;
        void iterate(frc::XboxController& pilot);

    private:
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX
            m_frontLeft{RobotMap::FRONT_LEFT_ID},
            m_rearLeft{RobotMap::REAR_LEFT_ID},
            m_frontRight{RobotMap::FRONT_RIGHT_ID},
            m_rearRight{RobotMap::REAR_RIGHT_ID};

        struct TalonRef {
            TalonRef(ctre::phoenix::motorcontrol::can::WPI_TalonSRX& r):ref(r){}
            ctre::phoenix::motorcontrol::can::WPI_TalonSRX& ref;
        };

        frc::MecanumDrive m_drive{
            m_frontLeft, 
            m_rearLeft, 
            m_frontRight,
            m_rearRight
        };
};