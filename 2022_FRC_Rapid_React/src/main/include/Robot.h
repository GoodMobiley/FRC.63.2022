// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include "RobotMap.h"

#include "subsystems/Drive.h"
#include "subsystems/Launcher.h"
#include "subsystems/Rake.h"
#include "subsystems/Climb.h"

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/DigitalInput.h>//<--Temp

#include <frc/Compressor.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  frc::XboxController 
    m_pilot{RobotMap::PILOT_CONTROLLER},
    m_copilot{RobotMap::COPILOT_CONTROLLER};

  frc::Compressor m_compressor{RobotMap::PCM_ID, frc::PneumaticsModuleType::CTREPCM};
  
  RapidReactDrive m_robotDrive;
  RapidReactLauncher m_robotLauncher;
  RapidReactRake m_robotRake;
  RapidReactClimb m_robotClimb;

  frc::DigitalInput //<--Temp
            m_leftLimitSwitch{RobotMap::LEFT_LIMIT_SWITCH_ID},
            m_rightLimitSwitch{RobotMap::RIGHT_LIMIT_SWITCH_ID};
};
