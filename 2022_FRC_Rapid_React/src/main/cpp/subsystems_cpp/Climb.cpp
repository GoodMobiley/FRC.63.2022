#include "subsystems/Climb.h"

#include <units/time.h>
#include <fmt/core.h>

RapidReactClimb::RapidReactClimb(){
    //Constructor: sets all motor properties
    m_leftHookMotor.SetInverted(false);
    m_leftHookMotor.SetSafetyEnabled(false);

    m_rightHookMotor.SetInverted(false);
    m_rightHookMotor.SetSafetyEnabled(false);

    m_hookRotationMotor.SetInverted(false);
    m_hookRotationEncoder.SetPosition(0);

    m_extentionTimer.Reset();   m_extentionTimer.Start();

    RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN);
}

void RapidReactClimb::Periodic(){
    if (m_climbing && m_climbTimer.Get() > m_climbStageTimestamps[m_climbStageCounter]){
        m_climbStageCounter++;
        if (m_climbStageCounter >= sizeof(m_climbStageTimestamps)/sizeof(m_climbStageTimestamps[0])){
            m_climbing = false;
        }
    }
    if (m_climbing){
        SetHookAngle(m_climbStageHookAngles[m_climbStageCounter]);
        switch (m_climbStageHookExtentions[m_climbStageCounter]){
            case -2:
                RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_CLIMB);
                break;
            case -1:
                RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN);
                break;
            case 1:
                ExtendHooks();
                break;
        }
    }

    if (m_extentionTimer.Get() > units::second_t(m_extentionTime) && m_hookExtentionStatus == 1){
        DisengageMotors();
        m_hookExtentionStatus = 2;
    }
    else if (m_hookExtentionStatus == -1){//|| m_hookExtentionStatus == -2){
        if (!m_leftLimitSwitch.Get()) {
            m_leftHookMotor.Set(-m_hookRetractPower);
        } else {
            m_leftHookMotor.StopMotor();
        }

        if (!m_rightLimitSwitch.Get()) {
            m_rightHookMotor.Set(-m_hookRetractPower);
        } else {
            m_rightHookMotor.StopMotor();
        }

        if (m_rightLimitSwitch.Get() && m_leftLimitSwitch.Get()){
            m_hookExtentionStatus = -2;
        }
    }

    m_hookRotation = m_hookRotationEncoder.GetPosition() / RobotMap::HOOK_ENCODER_UNITS_PER_REV * 360;
    if(m_hooksSet){
        if (m_hookRotation < m_targetHookRotation - m_angleFudge){
            m_hookRotationMotor.Set(RobotMap::HOOK_ROTATION_MOTOR_POWER);
        }
        else if (m_hookRotation > m_targetHookRotation + m_angleFudge){
            m_hookRotationMotor.Set(-RobotMap::HOOK_ROTATION_MOTOR_POWER);
        }
        else{
            m_hookRotationMotor.StopMotor();
        }
    }       
}
void RapidReactClimb::SimulationPeriodic(){

}

void RapidReactClimb::RetractHooks(double power){
    m_hookRetractPower = power;
    m_leftHookMotor.Set(-power);
    m_rightHookMotor.Set(-power);
    m_hookExtentionStatus = -1;
}
void RapidReactClimb::ExtendHooks(){
    if (m_hookExtentionStatus == -2){
        m_extentionTimer.Reset(); m_extentionTimer.Start();
        m_leftHookMotor.Set(RobotMap::HOOK_EXTEND_MOTOR_POWER);
        m_rightHookMotor.Set(RobotMap::HOOK_EXTEND_MOTOR_POWER);
        m_hookExtentionStatus = 1;
    }
}
void RapidReactClimb::DisengageMotors(){
    m_leftHookMotor.StopMotor();
    m_rightHookMotor.StopMotor();
}
void RapidReactClimb::ResetEncoders(){
    m_hookRotationEncoder.SetPosition(0);
    m_hooksSet = true;
    m_targetHookRotation = 0;
}
void RapidReactClimb::SetHookAngle(double angle){
    m_targetHookRotation = angle;
}
void RapidReactClimb::JogHookRotation(double power){
    m_hooksSet = false;
    m_hookRotationMotor.Set(power);
}
void RapidReactClimb::StartClimbCycle(){
    m_climbTimer.Reset();   m_climbTimer.Start();
    m_climbStageCounter = 0;
    m_climbing = true;
}
void RapidReactClimb::CancleClimbCycle(){
    m_climbing = false;
    m_hookExtentionStatus = 2;
}

void RapidReactClimb::Iterate(frc::XboxController & controller){
    if (m_climbing){
        if (controller.GetBButton()){
            CancleClimbCycle();
        }
    } else {
        if (controller.GetLeftTriggerAxis() > .5){
        JogHookRotation(RobotMap::HOOK_ROTATION_MOTOR_POWER/2);
        }
        else if (controller.GetLeftBumper()){
            JogHookRotation(-RobotMap::HOOK_ROTATION_MOTOR_POWER/2);
        }
        else if (!m_hooksSet){
            ResetEncoders();
        }

        if (controller.GetRightTriggerAxis() > .5){
        RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_CLIMB);
        }
        else if (controller.GetBButton()){
            RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN);
        }
        else if (controller.GetRightBumper()){
            ExtendHooks();
        }

        if (controller.GetAButton()){
            StartClimbCycle();
        }
    }
}

