#pragma once

#include "RobotMap.h"

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <rev/CANSparkMax.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <frc/DigitalInput.h>


#include <frc2/command/SubsystemBase.h>
#include <frc/XboxController.h>
#include <frc/Timer.h>

class RapidReactClimb: public frc2::SubsystemBase{
    public:
        RapidReactClimb();
        void ExtendHooks();
        void RetractHooks(double power);
        void DisengageMotors();
        void ResetEncoders();
        void SetHookAngle(double angle);
        void JogHookRotation(double power);
        void Iterate(frc::XboxController & controller);

        void Periodic() override;
        void SimulationPeriodic() override;

    private:
        double const 
            m_extentionTime = 1.85,
            m_angleFudge = 2;

        double 
            m_hookRotation = 0,
            m_targetHookRotation = RobotMap::HOOK_IDLE_POSE,
            m_hookRetractPower = RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN;

        int8_t m_hookExtentionStatus = 0; // -1: retracting, -2: retracted, 1: extending, 2: extended

        bool m_hooksSet = true;

        frc::Timer m_timer;

        rev::CANSparkMax m_hookRotationMotor{RobotMap::FRONT_HOOK_ROTATE_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::SparkMaxRelativeEncoder m_hookRotationEncoder = m_hookRotationMotor.GetEncoder(rev::CANEncoder::EncoderType::kHallSensor, 42);

        ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_leftHookMotor{RobotMap::LEFT_HOOK_MOTOR_ID};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX  m_rightHookMotor{RobotMap::RIGHT_HOOK_MOTOR_ID};

        frc::DigitalInput 
            m_leftLimitSwitch{RobotMap::LEFT_LIMIT_SWITCH_ID},
            m_rightLimitSwitch{RobotMap::RIGHT_LIMIT_SWITCH_ID};
};