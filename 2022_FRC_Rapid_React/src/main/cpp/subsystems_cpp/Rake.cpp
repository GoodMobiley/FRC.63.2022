#include "subsystems/Rake.h"

RapidReactRake::RapidReactRake(){
    m_rakeMotor.SetInverted(true);
    m_rakeMotor.SetSafetyEnabled(false);
}

void RapidReactRake::Periodic(){

}
void RapidReactRake::SimulationPeriodic(){

}

void RapidReactRake::LowerRake(){ m_rakeSolenoid.Set(frc::DoubleSolenoid::Value::kForward); }
void RapidReactRake::RaiseRake(){ m_rakeSolenoid.Set(frc::DoubleSolenoid::Value::kReverse); }
void RapidReactRake::EngageMotors(){ m_rakeMotor.Set(RobotMap::RAKE_MOTOR_POWER); }
void RapidReactRake::DisengageMotors(){ m_rakeMotor.StopMotor(); }

void RapidReactRake::EngageBallLoading(){
    LowerRake();
    EngageMotors();
}
void RapidReactRake::DisengageBallLoading(){
    RaiseRake();
    DisengageMotors();
}

void RapidReactRake::Iterate(frc::XboxController &controller){
    if (controller.GetAButton()){
        m_ballStaging = true;
    }
    else{
        m_ballStaging = false;
    }

    if(controller.GetPOV() == 0){
        m_rakeOn = false;
    }
    if(controller.GetPOV() == 180){
        m_rakeOn = true;
    }

    if(m_rakeOn || m_ballStaging){
        EngageMotors();
    }
    else{
        DisengageMotors();
    }

    if(m_rakeOn){
        LowerRake();
    }
    else{
        RaiseRake();
    }
}