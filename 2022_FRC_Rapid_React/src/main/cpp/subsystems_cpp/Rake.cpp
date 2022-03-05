#include "subsystems/Rake.h"

RapidReactRake::RapidReactRake(){
    m_rakeMotor.SetInverted(true);
    m_rakeMotor.SetSafetyEnabled(false);
    RaiseRake();
}

void RapidReactRake::Periodic(){
    if (m_rake || m_ballStaging){
        EngageMotors();
    } else {
        DisengageMotors();
    }
}
void RapidReactRake::SimulationPeriodic(){

}

void RapidReactRake::LowerRake(){ 
    m_rakeSolenoid.Set(frc::DoubleSolenoid::Value::kForward); 
}
void RapidReactRake::RaiseRake(){ 
    m_rakeSolenoid.Set(frc::DoubleSolenoid::Value::kReverse); 
}
void RapidReactRake::EngageMotors(){ 
    m_rakeMotor.Set(RobotMap::RAKE_MOTOR_POWER); 
}
void RapidReactRake::DisengageMotors(){ 
    m_rakeMotor.StopMotor(); 
}

void RapidReactRake::EngageRake(){
    LowerRake();
    m_rake = true;
}
void RapidReactRake::DisengageRake(){
    RaiseRake();
    m_rake = false;
}

void RapidReactRake::EngageBallStaging(){
    m_ballStaging = true;
}
void RapidReactRake::DisengageBallStaging(){
    m_ballStaging = false;
}

void RapidReactRake::Iterate(frc::XboxController &controller){
    if(controller.GetPOV() == 0){ 
        DisengageRake(); 
    }
    if(controller.GetPOV() == 180){ 
        EngageRake(); 
    }

    if(controller.GetLeftTriggerAxis() > .5) { 
        EngageBallStaging(); 
    } else { 
        DisengageBallStaging(); 
    }
}