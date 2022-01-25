#pragma once

#include "RobotMap.h"

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <frc/XboxController.h>

class SolenoidTest: public frc2::SubsystemBase{
    public:
        SolenoidTest();
        void Periodic() override;
        void SimulationPeriodic() override;

        void raiseClimb();
        void lowerClimb();

        void raiseHook();
        void lowerHook();

        void enable();
        void disable();

        void deployHook();
        void resetHook();

        void climb(double rate);

        void iterate(frc::XboxController &pilot);

    private:
        frc::Compressor m_compressor{RobotMap::PCM1_ID, frc::PneumaticsModuleType::CTREPCM};

        ctre::phoenix::motorcontrol::can::VictorSPX m_climbMotor{RobotMap::LEFT_WINCH_ID};

        frc::DoubleSolenoid 
            m_climbSolenoid{RobotMap::PCM1_ID, frc::PneumaticsModuleType::CTREPCM, RobotMap::CLIMB_EXTEND_SOLENOID, RobotMap::CLIMB_RETRACT_SOLENOID},

            m_hookSolenoid{RobotMap::PCM1_ID, frc::PneumaticsModuleType::CTREPCM, RobotMap::HOOK_EXTEND_SOLENOID, RobotMap::HOOK_RETRACT_SOLENOID},
            
            m_hookReleaseSolenoid{RobotMap::PCM2_ID, frc::PneumaticsModuleType::CTREPCM, RobotMap::HOOK_RELEASE_EXTEND_SOLENOID, RobotMap::HOOK_RELEASE_RETRACT_SOLENOID};
};