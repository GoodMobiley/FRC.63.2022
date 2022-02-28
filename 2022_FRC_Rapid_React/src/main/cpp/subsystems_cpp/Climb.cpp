#include "subsystems/Climb.h"

#include <fmt/core.h>

RapidReactClimb::RapidReactClimb(){

}

void RapidReactClimb::Periodic(){

}
void RapidReactClimb::SimulationPeriodic(){

}

void RapidReactClimb::Iterate(frc::XboxController & controller){
    if(controller.GetPOV() == 0){
        m_frontHookMotor.Set(RobotMap::FRONT_HOOK_MOTOR_POWER);
    }
    else if(controller.GetPOV() == 180){
        m_frontHookMotor.Set(-RobotMap::FRONT_HOOK_MOTOR_POWER);
    }

    /*if(!m_leftLimitSwitch.Get()){
        fmt::print("Left");
    }
    if(!m_rightLimitSwitch.Get()){
        fmt::print("Right");
    }*/
}

