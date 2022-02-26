#include "subsystems/Launcher.h"

#include <fmt/core.h>

RapidReactLauncher::RapidReactLauncher(){
    m_leftMotor.SetInverted(true);
    m_leftMotor.SetSafetyEnabled(false);

    m_rightMotor.SetInverted(true);
    m_rightMotor.SetSafetyEnabled(false);
}
void RapidReactLauncher::Periodic(){

}
void RapidReactLauncher::SimulationPeriodic(){
    
}
void RapidReactLauncher::EngageMotorsLong(){
    m_leftMotor.Set(RobotMap::LAUNCHER_MOTOR_POWER_LONG * .85);
    m_rightMotor.Set(RobotMap::LAUNCHER_MOTOR_POWER_LONG);
    m_motorsEngaged = true;
}
void RapidReactLauncher::EngageMotorsShort(){
    m_leftMotor.Set(RobotMap::LAUNCHER_MOTOR_POWER_SHORT * .85);
    m_rightMotor.Set(RobotMap::LAUNCHER_MOTOR_POWER_SHORT);
    m_motorsEngaged = true;
}
void RapidReactLauncher::DisengageMotors(){
    m_leftMotor.StopMotor();
    m_rightMotor.StopMotor();
    m_motorsEngaged = false;
}

void RapidReactLauncher::EngageBallStaging(){
    m_stagingSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    m_shovingSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}
void RapidReactLauncher::DisengageBallStaging(){
    m_stagingSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void RapidReactLauncher::LaunchBall(){
    if (m_motorsEngaged){
        m_shovingSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
}

void RapidReactLauncher::Iterate(frc::XboxController &controller){
    if(controller.GetAButtonPressed()){
        EngageBallStaging();
    }
    else if(controller.GetAButtonReleased()){
        DisengageBallStaging();
    }

    if(controller.GetRightTriggerAxis() > .5){
        if(!m_pressingTrigger){
            LaunchBall();
            EngageMotorsLong();
        }
        m_pressingTrigger = true;
    }
    else if(controller.GetRightBumper()){
        if(!m_pressingTrigger){
            LaunchBall();
            EngageMotorsShort();
        }
        m_pressingTrigger = true;
    }
    else{
        m_pressingTrigger = false;
    }

    if(controller.GetBButtonPressed()){
        DisengageMotors();
    }
}