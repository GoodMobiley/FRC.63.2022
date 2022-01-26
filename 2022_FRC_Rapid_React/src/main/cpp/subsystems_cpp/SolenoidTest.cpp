#include "subsystems/SolenoidTest.h"

SolenoidTest::SolenoidTest(){
    disable();
}

void SolenoidTest::Periodic(){

}

void SolenoidTest::SimulationPeriodic(){

}

void SolenoidTest::deployHook(){
    m_hookReleaseSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}

void SolenoidTest::resetHook(){
    m_hookReleaseSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void SolenoidTest::raiseClimb(){
    m_climbSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void SolenoidTest::lowerClimb(){
    m_climbSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}

void SolenoidTest::raiseHook(){
    m_hookSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

void SolenoidTest::lowerHook(){
    m_hookSolenoid.Set(frc::DoubleSolenoid::Value::kReverse);    
}

void SolenoidTest::climb(double rate){
    m_climbMotor.Set(ctre::phoenix::motorcontrol::VictorSPXControlMode::PercentOutput, rate);
}

void SolenoidTest::enable(){
    m_compressor.EnableDigital();
}

void SolenoidTest::disable(){
    m_compressor.Disable();

    m_climbSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
    m_hookSolenoid.Set(frc::DoubleSolenoid::Value::kOff);
}

void SolenoidTest::iterate(frc::XboxController& pilot){
    if(pilot.GetPOV() == 0){
        raiseClimb();
        raiseHook();
    }
    else if(pilot.GetPOV() == 180){
        lowerClimb();
        lowerHook();
    }

    if(pilot.GetAButtonPressed()){
        deployHook();
    }

    if(pilot.GetStartButtonPressed()){
        resetHook();
    }

    if(pilot.GetRightTriggerAxis() > .02){
        climb(pilot.GetRightTriggerAxis());
    }
    else if(pilot.GetRightBumper()){
        climb(-1);
    }
    else{
        climb(0);
    }
}