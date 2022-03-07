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

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  m_compressor.EnableDigital();
  m_robotClimb.ResetEncoders();
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
  m_robotClimb.Periodic();
  m_robotDrive.Periodic();
  m_robotLauncher.Periodic();
  m_robotRake.Periodic();
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
  m_robotDrive.ResetEncoders();
  m_robotLauncher.EngageMotors(RobotMap::SHORT_MOTOR_POWER);
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
    
  } else {
    // Default Auto goes here
  }
  double 
    distanceTraveled = -m_robotDrive.AverageEncoders() / RobotMap::ENCODER_UNITS_PER_REV * RobotMap::WHEEL_CIRCUMFRENCE, 
    targetDistance = 10;
  if (distanceTraveled < targetDistance) {
      m_robotDrive.Forward(((targetDistance + 2) - distanceTraveled) / targetDistance / 2);
  }
  else {
    m_robotLauncher.LaunchBall();
    m_robotLauncher.DisengageMotors();
  }
  fmt::print(std::to_string(distanceTraveled) + "\n");
}

void Robot::TeleopInit() {
  m_robotClimb.RetractHooks(RobotMap::HOOK_RETRACT_MOTOR_POWER_RETURN);
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

void Robot::DisabledPeriodic() {

}

void Robot::TestInit() {
  fmt::print("Test Start \n");
}

void Robot::TestPeriodic() {

}

void Robot::EngageBallStaging() {
  m_robotRake.EngageBallStaging();
  m_robotLauncher.EngageBallStaging();
}
void Robot::DisengageBallStaging() {
  m_robotRake.DisengageBallStaging();
  m_robotLauncher.DisengageBallStaging();
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
