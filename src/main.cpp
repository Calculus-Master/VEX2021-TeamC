/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       saptarshimallick                                          */
/*    Created:      Thu Jan 06 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// HookArms             motor_group   3, 4            
// ElevatorVision       vision        20              
// Inertial             inertial      10              
// CarryVision          vision        19              
// Optical              distance      16              
// CascadeArm           motor         6               
// TiltArm              motor         5               
// LeftMotor            motor_group   1, 9            
// RightMotor           motor_group   2, 8            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"

#include <cmath>

#include "Drive.h"
#include "ElevatorArmMotor.h"
#include "CarryArmDualMotors.h"
#include "CustomVisionSensor.h"

using namespace vex;
using namespace std;

vex::competition Competition;

//-------------------------Controls-------------------------------------
controller::axis leftDriveAxis() { return Controller1.Axis3; }
controller::axis rightDriveAxis() { return Controller1.Axis2; }

controller::button hookArmsUp() { return Controller1.ButtonL1; }
controller::button hookArmsDown() { return Controller1.ButtonL2; }

controller::button cascadeArmUp() { return Controller1.ButtonR1; }
controller::button cascadeArmDown() { return Controller1.ButtonR2; }

controller::button tiltArmsUp() { return Controller1.ButtonDown; }
controller::button tiltArmsDown() { return Controller1.ButtonUp; }

controller::button panicButton() { return Controller1.ButtonX; }

//-------------------------Auton----------------------------------------
void spinHookFor(int time, vex::directionType dir)
{
  HookArms.spin(dir); wait(time, msec); HookArms.stop();
}

void spinTiltFor(int time, vex::directionType direction)
{
  TiltArm.spin(direction); wait(time, msec); TiltArm.stop();
}

void spinCascadeFor(int time, vex::directionType direction)
{
  CascadeArm.spin(direction); wait(time, msec); CascadeArm.stop();
}

void driveFor(int time, int velocity)
{
  powerLeft(velocity); powerRight(velocity);
  wait(time, msec);
  LeftMotor.stop(); RightMotor.stop();
}

void powerFor(vex::turnType dir, int velocity, int time)
{
  if(dir == vex::left) powerLeft(velocity); else powerRight(velocity);
  wait(time, msec);
  if(dir == vex::left) LeftMotor.stop(); else RightMotor.stop();
}

void auton_Skills()
{
  spinCascadeFor(300, vex::reverse);

  //Blue 1
  driveFor(4000, -100);

  //Turn: Yellow 1
  driveFor(200, 100);
  powerFor(vex::left, 100, 400);

  //Yellow 1
  driveFor(3600, 100);

  //Turn: Yellow 2
  driveFor(100, -100);
  powerFor(vex::left, -100, 700);

  //Yellow 2
  driveFor(3400, -100);

  //Turn: Yellow 3
  driveFor(200, 100);
  powerFor(vex::left, 100, 800);

  //Yellow 3
  driveFor(2500, 100);
}

void auton_AllianceGoal()
{
  //Ready Tilt Arm
  spinTiltFor(300, vex::forward);

  //Bring down Hook Arms
  HookArms.spinFor(vex::forward, 320, degrees);

  //Drive to Goal
  driveFor(1300, 100);

  //Pick up Hook Arms
  spinHookFor(200, vex::reverse);

  //Tilt Back
  spinTiltFor(350, vex::reverse);

  //Drive back
  driveFor(1000, -100);
}

void auton_CenterGoal()
{
  //Ready Tilt Arm
  spinTiltFor(300, vex::forward);

  //Drive to Goal
  driveFor(3200, -100);

  //Tilt Back
  spinTiltFor(350, vex::reverse);

  //Drive back
  driveFor(2800, 100);
}

enum AutonPos
{
  ALLIANCE_GOAL,
  CENTER_GOAL,
  SKILLS
};

void auton(AutonPos pos)
{
  if(pos == SKILLS) auton_Skills(); else if(pos == ALLIANCE_GOAL) auton_AllianceGoal(); else if(pos == CENTER_GOAL) auton_CenterGoal();
}

//-------------------------Teleop---------------------------------------
void driver(CarryArmDualMotors hook, ElevatorArmMotor cascade, ElevatorArmMotor tilt)
{
  leftDriveAxis().changed([](){ powerLeft(leftDriveAxis().position()); });
  rightDriveAxis().changed([](){ powerRight(rightDriveAxis().position()); });

  hook.update(hookArmsUp().pressing(), hookArmsDown().pressing(), false);
  cascade.update(cascadeArmUp().pressing(), cascadeArmDown().pressing(), false);
  tilt.update(tiltArmsUp().pressing(), tiltArmsDown().pressing(), false);

  wait(100, msec);
}

void teleop()
{
  CarryArmDualMotors hook(HookArms, true, false);
  ElevatorArmMotor cascade(CascadeArm, true, false);
  ElevatorArmMotor tilt(TiltArm, true, false);

  while(true) driver(hook, cascade, tilt);
}

void panic()
{
  LeftMotor.stop();
  RightMotor.stop();
  HookArms.stop();
  CascadeArm.stop();
  TiltArm.stop();
}

void init()
{
  //Inertial
  Controller1.Screen.print("Inertial Sensor Calibration Started!");

  Inertial.calibrate();
  waitUntil(!Inertial.isCalibrating());

  Controller1.Screen.clearScreen();
  Controller1.Screen.print("Inertial Sensor Calibration Completed!");

  //Other Stuff
  HookArms.setVelocity(60, percent);
  HookArms.setMaxTorque(100, percent);

  CascadeArm.setVelocity(70, percent);
  CascadeArm.setMaxTorque(50, percent);

  TiltArm.setVelocity(45, percent);
  TiltArm.setMaxTorque(80, percent);

  HookArms.setStopping(hold);
  CascadeArm.setStopping(hold);
  TiltArm.setStopping(hold);

  panicButton().pressed(panic);

  Controller1.Screen.clearScreen();
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //Our Init
  init();

  Controller1.ButtonA.pressed(auton_Skills);

  //Competition Stuff
  Competition.drivercontrol(teleop);
  Competition.autonomous([](){ auton(CENTER_GOAL); });
}
