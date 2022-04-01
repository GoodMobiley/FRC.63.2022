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
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Timer.h>
#include <frc/Compressor.h>
//#include <hal/SimDevice.h>
//#include <hal/simulation/SimDeviceData.h>


class Robot : public frc::TimedRobot {
 public:
  void EngageBallStaging();
  void DisengageBallStaging();
  void RestartAutoTimer();

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
  frc::Timer m_autoTimer;
  int m_autoCounter = 0;

  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  frc::DigitalInput m_autoSwitch{1};

  //HAL_SimDeviceHandle dev = HALSIM_GetSimDeviceHandle("navX-Sensor[1]");
  //hal::SimDouble angle = HALSIM_GetSimValueHandle(dev, "Yaw");

  frc::XboxController 
    m_pilot{RobotMap::PILOT_CONTROLLER},
    m_copilot{RobotMap::COPILOT_CONTROLLER};

  frc::Compressor m_compressor{RobotMap::PCM_ID, frc::PneumaticsModuleType::CTREPCM};
  
  RapidReactDrive m_robotDrive;
  RapidReactLauncher m_robotLauncher;
  RapidReactRake m_robotRake;
  RapidReactClimb m_robotClimb;
};
