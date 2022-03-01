//Note, in c++, header files are kind of like class declarations and are initialized by a cpp file
//This file declares the drive subsystem class (RapidReactDrive)

#pragma once

#include "RobotMap.h"

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/XboxController.h>

class RapidReactDrive : public frc2::SubsystemBase {     //Declares the class, Lists all private and public variables and methods in the class
    public:
        RapidReactDrive();
        double AverageEncoders();
        void PrintEncoders();
        void Reverse(double power);
        void Forward(double power);
        void Iterate(frc::XboxController &controller);

        void Periodic() override;
        void SimulationPeriodic() override;
    private:
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX
            m_frontLeft{RobotMap::FRONT_LEFT_ID},
            m_rearLeft{RobotMap::REAR_LEFT_ID},
            m_frontRight{RobotMap::FRONT_RIGHT_ID},
            m_rearRight{RobotMap::REAR_RIGHT_ID};
        struct TalonRef {       //This is a special one, This creates a new variable type
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