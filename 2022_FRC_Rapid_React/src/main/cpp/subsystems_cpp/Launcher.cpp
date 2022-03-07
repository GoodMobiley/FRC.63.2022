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
void RapidReactLauncher::EngageMotors(double motorPower){
    m_leftMotor.Set(motorPower * 1);
    m_rightMotor.Set(motorPower * 1);
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
    else{
        fmt::print("Motors Not Engaged");
    }
}

void RapidReactLauncher::Iterate(frc::XboxController &controller){
    if      (controller.GetYButtonPressed()){EngageMotors(RobotMap::LONG_MOTOR_POWER);}
    else if (controller.GetXButtonPressed()){EngageMotors(RobotMap::SHORT_MOTOR_POWER);}
    else if (controller.GetAButtonPressed()){EngageMotors(RobotMap::PUKE_MOTOR_POWER);}
    else if (controller.GetBButtonPressed()){DisengageMotors();}

    if (controller.GetLeftTriggerAxis() > .5 || controller.GetLeftBumper()){
        EngageBallStaging();
    }
    else{
        DisengageBallStaging();
        if (controller.GetRightTriggerAxis() > .5){
            LaunchBall();
        }
    }
}