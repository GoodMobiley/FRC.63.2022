#pragma once

#include "RobotMap.h"

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <rev/CANSparkMax.h>
#include <rev/REVUtils.h>
#include <frc/DigitalInput.h>


#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <frc/Timer.h>

class RapidReactClimb: public frc2::SubsystemBase{
    public:
        RapidReactClimb();
        void RetractHooks();
        void ExtendHooks();
        void DisengageMotors();
        void ToggleHookExtention();
        void CancleHookCycle();
        void Iterate(frc::XboxController & controller);

        void Periodic() override;
        void SimulationPeriodic() override;

    private:
        double const m_extentionTime = .75;

        bool
            m_extendingHooks = false,
            m_hooksExtended = true,
            m_retractingHooks = true;

        frc::Timer m_timer;

        rev::CANSparkMax m_hookRotationMotor{
            RobotMap::FRONT_HOOK_ROTATE_ID, rev::CANSparkMax::MotorType::kBrushless
        };

        ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_leftHookMotor{RobotMap::LEFT_HOOK_MOTOR_ID};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX  m_rightHookMotor{RobotMap::RIGHT_HOOK_MOTOR_ID};

        frc::DigitalInput 
            m_leftLimitSwitch{RobotMap::LEFT_LIMIT_SWITCH_ID},
            m_rightLimitSwitch{RobotMap::RIGHT_LIMIT_SWITCH_ID};
};