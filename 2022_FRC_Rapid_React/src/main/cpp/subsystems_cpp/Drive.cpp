#include "subsystems/Drive.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <fmt/core.h>

using namespace std;

RapidReactDrive::RapidReactDrive() //Constructor Method (A function with the same name of a class defined in the class runs on the creation of a new child of the class) 
{
    m_drive.SetDeadband(.2); //sets the min value of joystic input

    m_frontLeft.SetInverted(false);  //Sets both right motors to reverse when receving a positive input (Adjusts for Mecanum Drive)
    m_rearLeft.SetInverted(false);
    m_frontRight.SetInverted(true);
    m_rearRight.SetInverted(false);

    TalonRef talons[] = 
    {
        m_frontLeft,
        m_rearLeft,
        m_frontRight,
        m_rearRight
    };

    for(TalonRef talon : talons)
    {
        talon.ref.ConfigNominalOutputForward(0.0, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.ConfigNominalOutputReverse(0.0, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.ConfigPeakOutputForward(1.0, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.ConfigPeakOutputReverse(-1.0, RobotMap::CAN_TIME_OUT_MS);
        //talon.ref.ConfigVoltageCompSaturation(11.0, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.EnableVoltageCompensation(false);

        talon.ref.Config_kP(0, 0.375, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.Config_kI(0, 0.0, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.Config_kD(0, 0.0, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.Config_kF(0, 0.35, RobotMap::CAN_TIME_OUT_MS);

        talon.ref.SelectProfileSlot(0, 0);
        talon.ref.ConfigClosedLoopPeakOutput(0, 1.0, RobotMap::CAN_TIME_OUT_MS);

        //sets sensor to mag encoder
        talon.ref.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, RobotMap::CAN_TIME_OUT_MS);
        talon.ref.ConfigSelectedFeedbackCoefficient(1.0, 0, RobotMap::CAN_TIME_OUT_MS);
    }
}

double RapidReactDrive::AveragePosition(){
    return(double) (
        -m_frontLeft.GetSelectedSensorPosition()-
        m_frontRight.GetSelectedSensorPosition()-
        m_rearLeft.GetSelectedSensorPosition()+
        m_rearRight.GetSelectedSensorPosition()
    ) / 4;
}
double RapidReactDrive::AverageVelocity(){
    return(double) (
        -m_frontLeft.GetSelectedSensorVelocity()-
        m_frontRight.GetSelectedSensorVelocity()-
        m_rearLeft.GetSelectedSensorVelocity()+
        m_rearRight.GetSelectedSensorVelocity()
    ) / 4;
}
void RapidReactDrive::ResetEncoders(){
    m_frontLeft.SetSelectedSensorPosition(0);
    m_frontRight.SetSelectedSensorPosition(0);
    m_rearLeft.SetSelectedSensorPosition(0);
    m_rearRight.SetSelectedSensorPosition(0);
}

void RapidReactDrive::PrintEncoders(){
    TalonRef talons[] = 
    {
        m_frontLeft,
        m_rearLeft,
        m_frontRight,
        m_rearRight
    };

    for(TalonRef talon : talons)
    {
        fmt::print(
            "Talon ID: " + to_string(talon.ref.GetDeviceID()) + "     " +
            "Sensor Pos: " + to_string(talon.ref.GetSelectedSensorPosition()) + "     " +
            "Sensor Vel: " + to_string(talon.ref.GetSelectedSensorVelocity()) + "\n"
        );
    }
}

void RapidReactDrive::Periodic(){
    //fmt::print(std::to_string(AverageEncoders()) + "\n");
}

void RapidReactDrive::SimulationPeriodic(){

}

void RapidReactDrive::Reverse(double power){
    m_drive.DriveCartesian(-power, 0, 0, 0);
}

void RapidReactDrive::Forward(double power){
    m_drive.DriveCartesian(power, 0, 0, 0);
}

void RapidReactDrive::Iterate(frc::XboxController &controller){
    m_drive.DriveCartesian(
        pow(-controller.GetLeftY(), 1) * .8, 
        pow(controller.GetLeftX(), 1) * .8, 
        pow(controller.GetRightX(), 1) * .8,
        0
    );
}