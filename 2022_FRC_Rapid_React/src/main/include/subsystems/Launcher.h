#pragma once

#include "RobotMap.h"
#include "subsystems/Rake.h"

#include <frc/motorcontrol/Spark.h>
#include <frc/DoubleSolenoid.h>

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>

class RapidReactLauncher: public frc2::SubsystemBase{
    public:
        RapidReactLauncher();
        void EngageMotorsLong();
        void EngageMotorsShort();
        void DisengageMotors();
        void EngageBallStaging();
        void DisengageBallStaging();
        void LaunchBall();
        void Iterate(frc::XboxController &controller);

        void Periodic() override;
        void SimulationPeriodic() override;
    private:
        bool 
            m_motorsEngaged = false,
            m_pressingTrigger = false;
        frc::Spark
            m_leftMotor{RobotMap::LEFT_LAUNCHER_MOTOR},
            m_rightMotor{RobotMap::RIGHT_LAUNCHER_MOTOR};
        frc::DoubleSolenoid 
            m_stagingSolenoid{RobotMap::PCM_ID, frc::PneumaticsModuleType::CTREPCM, RobotMap::BALL_STAGE_EXTEND_SOLENOID, RobotMap::BALL_STAGE_RETRACT_SOLENOID},
            m_shovingSolenoid{RobotMap::PCM_ID, frc::PneumaticsModuleType::CTREPCM, RobotMap::BALL_SHOVER_EXTEND_SOLENOID, RobotMap::BALL_SHOVER_RETRACT_SOLENOID};
};