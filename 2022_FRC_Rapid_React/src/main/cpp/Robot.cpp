// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//You already know what this does...
#include "Robot.h"

#include <math.h>

#include <cameraserver/CameraServer.h>
#include <fmt/core.h>
#include <frc2/command/Subsystem.h>
#include <frc/smartdashboard/SmartDashboard.h>

//Declares this function (defined below)
void printControllerCond(frc::XboxController& controller);

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_compressor.EnableDigital();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  m_autoSelected = frc::SmartDashboard::GetString("Auto Selector",
       kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
    double 
      distanceTraveled = m_robotDrive.AverageEncoders() / RobotMap::ENCODER_UNITS_PER_REV * RobotMap::WHEEL_CIRCUMFRENCE, 
      targetDistance = 10;
    if (distanceTraveled < targetDistance) {
       m_robotDrive.Forward(((targetDistance + 1) - distanceTraveled) / 20);
    }
    else {
      m_robotLauncher.LaunchBall();
    }
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {

}

void Robot::TeleopPeriodic() {
  m_robotDrive.Iterate(m_pilot);
  m_robotClimb.Iterate(m_pilot);
  m_robotLauncher.Iterate(m_copilot);
  m_robotRake.Iterate(m_copilot);
}

void Robot::DisabledInit() {
  m_robotLauncher.DisengageMotors();
}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {
  fmt::print("Test Start \n");
}

void Robot::TestPeriodic() {

}

//This puppy prints out all the active axies of the controller when called
void printControllerCond(frc::XboxController &controller){
  std::string space = "     ";
  fmt::print(
    "X: " + std::to_string( -controller.GetLeftY()  ) + space + 
    "Y: " + std::to_string(  controller.GetLeftX()  ) + space +
    "Z: " + std::to_string(  controller.GetRightX() ) + "\n"
  );
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
