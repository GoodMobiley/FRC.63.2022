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

    m_extensionTimer.Reset();   m_extensionTimer.Start();

    RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN);
}

void RapidReactClimb::Periodic(){
    if (m_hookExtensionStatus == 1){
        if (m_extensionTimer.Get() > m_leftExtensionTime){
            m_leftHookMotor.StopMotor();
        }
        if (m_extensionTimer.Get() > m_rightExtensionTime){
            m_rightHookMotor.StopMotor();
        }
        if ((m_leftExtensionTime >= m_rightExtensionTime && m_extensionTimer.Get() > m_leftExtensionTime) ||
            (m_rightExtensionTime > m_leftExtensionTime && m_extensionTimer.Get() > m_rightExtensionTime)){
            DisengageMotors();
            fmt::print("[Climb] Hooks Extended\n");
            m_hookExtensionStatus = 2;
        }
    }
    else if (m_hookExtensionStatus == -1){//|| m_hookExtentionStatus == -2){
        if (m_rightLimitSwitch.Get() && m_leftLimitSwitch.Get()){
            fmt::print("[Climb] Hooks Retracted\n");
            m_hookExtensionStatus = -2;
        }
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
    }

    m_hookRotation = m_hookRotationEncoder.GetPosition() / RobotMap::HOOK_ENCODER_UNITS_PER_REV * 360;
    if(m_hooksSet){
        if (m_hookRotation < m_targetHookRotation + m_hookTargetOffset - m_angleFudge){
            m_hookRotationMotor.Set(RobotMap::HOOK_ROTATION_MOTOR_POWER);
        }
        else if (m_hookRotation > m_targetHookRotation + m_hookTargetOffset + m_angleFudge){
            m_hookRotationMotor.Set(-RobotMap::HOOK_ROTATION_MOTOR_POWER);
        }
        else{
            m_hookRotationMotor.StopMotor();
        }
    }

    switch(m_climbStageCounter){
        case 0:
            if (m_hookExtensionStatus == -2){//go to next stage if hooks retracted
                m_climbStageCounter++;
                m_climbTimer.Reset();   m_climbTimer.Start();
                break;
            }
            SetHookAngle(0);
            RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_CLIMB);
            break;
        case 1:
            if(m_climbTimer.Get() > .25_s){//go to next stage after .5 sec
                m_climbStageCounter++;
                break;
            }
            ExtendHooks();
            break;
        case 2:
            if(m_hookExtensionStatus == -2){//go to next stage if hooks retracted
                m_climbStageCounter++;
                break;
            }
            RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN);
            break;
        case 3:
            if(HookRotationAt(-40)){//go to next stage if hooks at -40 deg
                m_climbStageCounter++;
                break;
            }
            SetHookAngle(-40);
            RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN);
            break;
        case 4:
            if(m_hookExtensionStatus == 2){//go to next stage if hooks extended
                m_climbStageCounter++;
                break;
            }
            ExtendHooks();
            break;
        case 5:
            if(HookRotationAt(-60)){//go to next stage if hooks at -60
                m_climbStageCounter++;
                m_climbTimer.Reset();   m_climbTimer.Start();
                break;
            }
            SetHookAngle(-60);
            break;
        case 6:
            if(m_climbTimer.Get() > 1.25_s){//go to next stage after 1.25 sec
                m_climbStageCounter++;
                break;
            }
            RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_CLIMB);
            break;
        case 7:
            if(m_hookExtensionStatus == -2){//Ends the climb cycle when hooks are retracted
                fmt::print("[Climb] Completed Automatic Climb Cycle\n");
                m_climbStageCounter++;
                break;
            }
            RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_CLIMB);
            SetHookAngle(0);
            break;
        default:

            break;
    }
}
void RapidReactClimb::SimulationPeriodic(){

}

void RapidReactClimb::RetractHooks(double power){
    if (m_hookExtensionStatus != -1){
        fmt::print("[Climb] Retracting Hooks\n");
    }
    m_hookRetractPower = power;
    m_leftHookMotor.Set(-power);
    m_rightHookMotor.Set(-power);
    m_hookExtensionStatus = -1;
}
void RapidReactClimb::ExtendHooks(){
    if (m_hookExtensionStatus == -2){
        fmt::print("[Climb] Extending Hooks\n");
        m_extensionTimer.Reset(); m_extensionTimer.Start();
        m_leftHookMotor.Set(RobotMap::HOOK_EXTEND_MOTOR_POWER);
        m_rightHookMotor.Set(RobotMap::HOOK_EXTEND_MOTOR_POWER);
        m_hookExtensionStatus = 1;
    }
}
void RapidReactClimb::DisengageMotors(){
    m_leftHookMotor.StopMotor();
    m_rightHookMotor.StopMotor();
}
void RapidReactClimb::ResetEncoders(){
    if (!m_hooksSet){
        fmt::print("[Climb] Reset Hook Encoders\n");
    }
    m_hookRotationEncoder.SetPosition(0);
    m_hooksSet = true;
    m_targetHookRotation = 0;
}
void RapidReactClimb::SetHookTargetOffset(){
    if (!m_hooksSet){
        fmt::print("[Climb] Set Hook Target Angle Offset To" + std::to_string(m_hookRotation) + "deg.\n");
    }
    m_hookTargetOffset = m_hookRotation;
    m_hooksSet = true;
    m_targetHookRotation = 0;
}
void RapidReactClimb::SetHookAngle(double angle){
    if(m_targetHookRotation != angle){
        fmt::print("[Climb] Set Hook Angle To: " + std::to_string(angle) + " deg.\n");
    }
    m_targetHookRotation = angle;
}
void RapidReactClimb::JogHookRotation(double power){
    m_hooksSet = false;
    m_hookRotationMotor.Set(power);
}
bool RapidReactClimb::HookRotationAt(double angle){
    m_hookRotation = m_hookRotationEncoder.GetPosition() / RobotMap::HOOK_ENCODER_UNITS_PER_REV * 360;
    return (m_hookRotation > angle - m_angleFudge && m_hookRotation < angle + m_angleFudge);
}

void RapidReactClimb::StartClimbCycle(){
    fmt::print("[Climb] Starting Automatic Climb Cycle\n");
    m_climbStageCounter = 0;
}
void RapidReactClimb::CancleClimbCycle(){
    fmt::print("[Climb] Cancling Automatic Climb Cycle\n");
    m_climbStageCounter = 8;
    m_hookExtensionStatus = 2;
    SetHookAngle(0);
}

void RapidReactClimb::Iterate(frc::XboxController & controller){
    if (m_climbStageCounter < 8){
        if (controller.GetBButton()){
            CancleClimbCycle();
        }
    } else {
        if (controller.GetLeftTriggerAxis() > .5){
            JogHookRotation(RobotMap::HOOK_ROTATION_MOTOR_POWER);
        }
        else if (controller.GetLeftBumper()){
            JogHookRotation(-RobotMap::HOOK_ROTATION_MOTOR_POWER);
        }
        else if (!m_hooksSet){
            SetHookTargetOffset();
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

        if (controller.GetAButtonPressed()){
            StartClimbCycle();
        }
    }
}