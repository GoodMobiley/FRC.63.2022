#include "subsystems/Launcher.h"
#include <units/time.h>
#include <units/voltage.h>

RapidReactLauncher::RapidReactLauncher(){
    m_leftMotor.SetSafetyEnabled(false);
    //m_leftMotor.SetExpiration(units::time::second_t(.1));
    //m_leftMotor.Feed();

    m_rightMotor.SetSafetyEnabled(false);
    //m_rightMotor.SetExpiration(units::time::second_t(.1));
    //m_rightMotor.Feed();
}
void RapidReactLauncher::Periodic(){

}
void RapidReactLauncher::SimulationPeriodic(){
    
}
void RapidReactLauncher::EngageMotors(double setValue){
    m_leftMotor.Set(setValue);
    m_rightMotor.Set(setValue);
}
void RapidReactLauncher::DisengageMotors(){
    m_leftMotor.StopMotor();
    m_rightMotor.StopMotor();
}