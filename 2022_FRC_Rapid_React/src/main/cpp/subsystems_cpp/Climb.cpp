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
    m_hookRotationMotor.SetSafetyEnabled(false);

    m_timer.Reset();
    m_timer.Start();
}

void RapidReactClimb::Periodic(){
    if (m_timer.Get() > units::second_t(m_extentionTime) && m_extendingHooks){
        m_extendingHooks = false;
        m_hooksExtended = true;
    }

    if(m_retractingHooks){
        RetractHooks();
    }
    else if(m_extendingHooks){
        ExtendHooks();
    }
    else{
        DisengageMotors();
    }
}
void RapidReactClimb::SimulationPeriodic(){

}

void RapidReactClimb::RetractHooks(){
    //retracts left if not right limit switch
    if (!m_leftLimitSwitch.Get())   {m_leftHookMotor.Set(-RobotMap::HOOK_EXTEND_MOTOR_POWER);}
    else {m_leftHookMotor.StopMotor();}

    //retracts right if not right limit switch
    if (!m_rightLimitSwitch.Get())  {m_rightHookMotor.Set(-RobotMap::HOOK_EXTEND_MOTOR_POWER);}
    else {m_rightHookMotor.StopMotor();}

    if(m_rightLimitSwitch.Get() && m_leftLimitSwitch.Get()){
        m_retractingHooks = false;
        m_hooksExtended = false;
    }
}
void RapidReactClimb::ExtendHooks(){
    m_leftHookMotor.Set(RobotMap::HOOK_EXTEND_MOTOR_POWER);
    m_rightHookMotor.Set(RobotMap::HOOK_EXTEND_MOTOR_POWER);
}
void RapidReactClimb::DisengageMotors(){
    m_leftHookMotor.StopMotor();
    m_rightHookMotor.StopMotor();
}
void RapidReactClimb::ToggleHookExtention(){
    if (!m_retractingHooks && !m_extendingHooks){
        if (m_hooksExtended){
            m_retractingHooks = true;
        }
        else{
            m_timer.Reset();
            m_timer.Start();
            m_extendingHooks = true;
        }
    }
}
void RapidReactClimb::CancleHookCycle(){
    m_extendingHooks = false;
    m_retractingHooks = false;
    m_hooksExtended = true;
    DisengageMotors();
}

void RapidReactClimb::Iterate(frc::XboxController & controller){
    if(controller.GetBButton()){
        m_hookRotationMotor.Set(RobotMap::HOOK_ROTATION_MOTOR_POWER);
    }
    else if (controller.GetXButton()){
        m_hookRotationMotor.Set(-RobotMap::HOOK_ROTATION_MOTOR_POWER);
    }

    if(controller.GetAButtonPressed()){
        ToggleHookExtention();
    }
    else if(controller.GetBButton()){
        CancleHookCycle();
    }
}

