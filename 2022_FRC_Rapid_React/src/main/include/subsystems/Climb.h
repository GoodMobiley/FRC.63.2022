#pragma once

#include "RobotMap.h"

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/DigitalInput.h>

#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>

class RapidReactClimb: public frc2::SubsystemBase{
    public:
        RapidReactClimb();
        void Iterate(frc::XboxController & controller);

        void Periodic() override;
        void SimulationPeriodic() override;

    private:
        frc::PWMSparkMax m_frontHookMotor{RobotMap::FRONT_ARM_ROTATE_ID};

        /*frc::DigitalInput 
            m_leftLimitSwitch{RobotMap::LEFT_LIMIT_SWITCH_ID},
            m_rightLimitSwitch{RobotMap::RIGHT_LIMIT_SWITCH_ID};*/
};