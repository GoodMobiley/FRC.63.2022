#include "subsystems/Rake.h"

#include <fmt/core.h>

RapidReactRake::RapidReactRake(){
    m_rakeMotor.SetInverted(true);
    m_rakeMotor.SetSafetyEnabled(false);
    DisengageRake();
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

void RapidReactRake::EngageMotors(){ 
    m_rakeMotor.Set(RobotMap::RAKE_MOTOR_POWER); 
}
void RapidReactRake::DisengageMotors(){ 
    m_rakeMotor.StopMotor(); 
}

void RapidReactRake::EngageRake(){
    if (!m_rake){
        fmt::print("[Rake] Rake Engaged\n");
    }
    m_rake = true;
    m_rakeSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}
void RapidReactRake::DisengageRake(){
    if (m_rake){
        fmt::print("[Rake] Rake Disengaged\n");
    }
    m_rake = false;
    m_rakeSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}

void RapidReactRake::Iterate(frc::XboxController &controller){
    if(controller.GetPOV() == 0){ 
        DisengageRake(); 
    }
    if(controller.GetPOV() == 180){ 
        EngageRake(); 
    }

    if(controller.GetLeftTriggerAxis() > .5) { 
        if (!m_ballStaging){
            fmt::print("[Rake] Engaged Motors For Ball Staging\n");
        }
        m_ballStaging = true;
    } else { 
        if (m_ballStaging){
            fmt::print("[Rake] Disengaged Rake Motors\n");
        }
        m_ballStaging = false;
    }
}