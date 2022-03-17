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
        void StartClimbCycle();
        void CancleClimbCycle();
        void Iterate(frc::XboxController & controller);

        void Periodic() override;
        void SimulationPeriodic() override;

    private:
        const double
            m_angleFudge = 2,
            m_climbStageHookAngles[8] {//angle of front hooks per auto-climb stage
                0,  //0: straight up
                10,  //1: lean backward 5 degrees
                10,  //2: stay at 5
                -30, //3: lean forward 5 degrees
                -30, //4: stay at -5
                -30,//5: lean forward 10 degrees
                -40,//6: rotate for handoff
                0   //7: rotate back to 0
            }; 
        const int8_t 
            m_climbStageHookExtentions[8] {//-1: retract return, -2: retract climb, 1: extend
                -2, //0: climb
                1,  //1:  (Slight Extend
                -1, //2:  & Retract)
                -1, //3: stay retracted
                1,  //4: extend
                1,  //5: stay extended
                -2, //6: climb
                0   //7: do nothing (retract till retracted)
            };
        const units::second_t
            m_extentionTime = 2.1_s,
            m_climbStageTimestamps[8] {2_s, 1_s, 1_s, 1_s, 1_s, 1_s, 1_s, 1.3_s}; //time that the program switches climb stages (in seconds between stages) (tbd)

        double 
            m_hookRotation = 0,
            m_targetHookRotation = 0,
            m_hookRetractPower = RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN;

        int8_t 
            m_hookExtentionStatus = 0, // -1: retracting, -2: retracted, 1: extending, 2: extended
            m_climbStageCounter = 0;

        bool 
            m_hooksSet = true,
            m_climbing = false;

        frc::Timer 
            m_extentionTimer,
            m_climbTimer;

        rev::CANSparkMax m_hookRotationMotor{RobotMap::FRONT_HOOK_ROTATE_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::SparkMaxRelativeEncoder m_hookRotationEncoder = m_hookRotationMotor.GetEncoder(rev::CANEncoder::EncoderType::kHallSensor, 42);

        ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_leftHookMotor{RobotMap::LEFT_HOOK_MOTOR_ID};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX  m_rightHookMotor{RobotMap::RIGHT_HOOK_MOTOR_ID};

        frc::DigitalInput 
            m_leftLimitSwitch{RobotMap::LEFT_LIMIT_SWITCH_ID},
            m_rightLimitSwitch{RobotMap::RIGHT_LIMIT_SWITCH_ID};
};