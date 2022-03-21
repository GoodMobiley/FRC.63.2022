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
    if (m_leftMotor.Get() != motorPower || !m_motorsEngaged){
        fmt::print("[Launcher] Motors Engaged; Motor Power: " + std::to_string(motorPower) + "\n");
    }
    m_motorsEngaged = true;
    m_motorWarned = false;
    m_leftMotor.Set(motorPower * 1);
    m_rightMotor.Set(motorPower * 1);
}
void RapidReactLauncher::DisengageMotors(){
    if (m_motorsEngaged){
        fmt::print("[Launcher] Motors Disengaged\n");
    }
    m_motorsEngaged = false;
    m_leftMotor.StopMotor();
    m_rightMotor.StopMotor();
}

void RapidReactLauncher::StageBall(){
    if (m_ballLaunched){
        fmt::print("[Launcher] Staged For Next Ball\n");
    }
    m_ballLaunched = false;
    m_motorWarned = false;
    m_shovingSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void RapidReactLauncher::LaunchBall(){
    if (!m_ballLaunched && m_motorsEngaged){
        fmt::print("[Launcher] Launched Ball\n");
    }
    else if (!m_motorWarned){
        m_motorWarned = true;
        fmt::print("[Launcher] Can't Launch While Motors Disengaged\n");
    }

    if (m_motorsEngaged){
        m_ballLaunched = true;
        m_shovingSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
    }
}

void RapidReactLauncher::Iterate(frc::XboxController &controller){
    if      (controller.GetYButtonPressed()){EngageMotors(RobotMap::LONG_MOTOR_POWER);}
    else if (controller.GetXButtonPressed()){EngageMotors(RobotMap::SHORT_MOTOR_POWER);}
    else if (controller.GetAButtonPressed()){EngageMotors(RobotMap::PUKE_MOTOR_POWER);}
    else if (controller.GetBButtonPressed()){DisengageMotors();}

    if (controller.GetRightTriggerAxis() > .5){
        LaunchBall();
    } else {
        StageBall();
    }
}