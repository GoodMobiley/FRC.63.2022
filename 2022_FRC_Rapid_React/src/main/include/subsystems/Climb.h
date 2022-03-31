#pragma once

#include "RobotMap.h"

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <rev/CANSparkMax.h>
#include <rev/SparkMaxRelativeEncoder.h>
#include <frc/DigitalInput.h>

#include <units/time.h>
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
        bool HookRotationAt(double angle);
        void StartClimbCycle();
        void CancleClimbCycle();
        void Iterate(frc::XboxController & controller);

        void Periodic() override;
        void SimulationPeriodic() override;

    private:
        const double
            m_angleFudge = 2;
        const units::second_t
            m_leftExtensionTime = 1.9_s,
            m_rightExtensionTime = 2.1_s;

        double 
            m_hookRotation = 0,
            m_targetHookRotation = 0,
            m_hookRetractPower = RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN;

        int8_t 
            m_hookExtensionStatus = 0, // -1: retracting, -2: retracted, 1: extending, 2: extended
            m_climbStageCounter = 8;

        bool 
            m_hooksSet = true;

        frc::Timer 
            m_extensionTimer,
            m_climbTimer;

        rev::CANSparkMax m_hookRotationMotor{RobotMap::FRONT_HOOK_ROTATE_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::SparkMaxRelativeEncoder m_hookRotationEncoder = m_hookRotationMotor.GetEncoder(rev::CANEncoder::EncoderType::kHallSensor, 42);

        ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_leftHookMotor{RobotMap::LEFT_HOOK_MOTOR_ID};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX  m_rightHookMotor{RobotMap::RIGHT_HOOK_MOTOR_ID};

        frc::DigitalInput 
            m_leftLimitSwitch{RobotMap::LEFT_LIMIT_SWITCH_ID},
            m_rightLimitSwitch{RobotMap::RIGHT_LIMIT_SWITCH_ID};
};