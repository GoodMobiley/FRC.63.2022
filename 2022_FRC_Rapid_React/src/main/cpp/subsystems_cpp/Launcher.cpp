#include "subsystems/Launcher.h"

#include <fmt/core.h>

RapidReactLauncher::RapidReactLauncher(){
    m_leftMotor.SetInverted(false);
    m_leftMotor.SetSafetyEnabled(false);

    m_rightMotor.SetInverted(false);
    m_rightMotor.SetSafetyEnabled(false);
}
void RapidReactLauncher::Periodic(){

}
void RapidReactLauncher::SimulationPeriodic(){
    
}
void RapidReactLauncher::EngageMotors(){
    m_leftMotor.Set(RobotMap::LAUNCHER_MOTOR_POWER);
    m_rightMotor.Set(RobotMap::LAUNCHER_MOTOR_POWER);
    m_motorsEngaged = true;
}
void RapidReactLauncher::DisengageMotors(){
    m_leftMotor.StopMotor();
    m_rightMotor.StopMotor();
    m_motorsEngaged = false;
}

void RapidReactLauncher::EngageBallStaging(){
    m_stageMotor.Set(.5);
    m_stagingSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    m_shovingSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}
void RapidReactLauncher::DisengageBallStaging(){
    m_stageMotor.StopMotor();
    m_stagingSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void RapidReactLauncher::LaunchBall(){
    if (m_motorsEngaged){
        m_shovingSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
    else{
        fmt::print("Motors Weren't Engaged!");
        EngageMotors();
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