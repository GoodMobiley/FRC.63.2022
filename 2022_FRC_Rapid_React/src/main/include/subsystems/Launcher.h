#pragma once

#include "RobotMap.h"

#include <frc/motorcontrol/Spark.h>
#include <frc/DoubleSolenoid.h>

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>

class RapidReactLauncher: public frc2::SubsystemBase{
    public:
        RapidReactLauncher();
        void EngageMotors(double setValue);
        void DisengageMotors();
        void Periodic() override;
        void SimulationPeriodic() override;
    private:
        frc::Spark
            m_leftMotor{RobotMap::LEFT_LAUNCHER_MOTOR},
            m_rightMotor{RobotMap::RIGHT_LAUNCHER_MOTOR};
        frc::DoubleSolenoid 
            m_loaderSolenoid{RobotMap::PCM_ID, frc::PneumaticsModuleType::CTREPCM, RobotMap::BALL_LOADER_EXTEND_SOLENOID, RobotMap::BALL_LOADER_RETRACT_SOLENOID},
            m_shoverSolenoid{RobotMap::PCM_ID, frc::PneumaticsModuleType::CTREPCM, RobotMap::BALL_SHOVER_EXTEND_SOLENOID, RobotMap::BALL_SHOVER_RETRACT_SOLENOID};
};