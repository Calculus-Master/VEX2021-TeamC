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
// LeftMotor            motor         2               
// RightMotor           motor         1               
// FrontArms            motor_group   3, 4            
// BackVision           vision        20              
// Inertial             inertial      10              
// FrontVision          vision        19              
// Optical              distance      16              
// CascadeArm           motor         6               
// TiltArm              motor         5               
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

controller::axis leftDriveAxis() { return Controller1.Axis3; }
controller::axis rightDriveAxis() { return Controller1.Axis2; }

controller::button frontArmsUp() { return Controller1.ButtonR1; }
controller::button frontArmsDown() { return Controller1.ButtonL1; }

controller::button backArmsUp() { return Controller1.ButtonR2; }
controller::button backArmsDown() { return Controller1.ButtonL2; }

controller::button tiltArmsDown() { return Controller1.ButtonDown; }
controller::button tiltArmsUp() { return Controller1.ButtonUp; }

controller::button alignVision() { return Controller1.ButtonY; }

controller::button panicButton() { return Controller1.ButtonX; }

controller::button autonButton() { return Controller1.ButtonB; }

void turn(vex::turnType turn, int deg)
{
  LeftMotor.setVelocity(100, percent);
  RightMotor.setVelocity(100, percent);

  if (turn == right) {
    LeftMotor.spinFor(vex::forward, deg, degrees);
    RightMotor.spinFor(vex::reverse, deg, degrees);
  }
  else {
    RightMotor.spinFor(vex::forward, deg, degrees);
    LeftMotor.spinFor(vex::reverse, deg, degrees);
  }
}

void powerFor(bool left, int velocity, int time)
{
  if(left) powerLeft(velocity);
  else powerRight(velocity);

  wait(time, msec);

  if(left) LeftMotor.stop();
  else RightMotor.stop();
}

enum StartPos
{
  BLUE_LEFT,
  BLUE_RIGHT,
  RED_LEFT,
  RED_RIGHT,
  SKILLS
};

void autoDrive(int time, int velocity)
{
  powerLeft(velocity);
  powerRight(velocity);

  wait(time, msec);

  LeftMotor.stop();
  RightMotor.stop();
}

void skills()
{
  //Drop Carry Arms
  //FrontArms.spinFor(vex::forward, 200, degrees);

  //Drop Elevator Arm
  TiltArm.spinFor(vex::reverse, 100, degrees);

  //Push Yellow 1
  autoDrive(6000, 100);

  //Turn Yellow 2
  powerFor(false, -100, 1050);

  //Push Yellow 2
  autoDrive(5500, -100);

  //Drive out a little
  autoDrive(700, 100);

  //Turn Yellow 3
  powerFor(true, -100, 1600);
  powerFor(false, 100, 200);

  //Push Yellow 3
  autoDrive(5000, 100);
}

void auton(StartPos pos)
{
  //Ditch old stuff because Hardcoding is the best
  if(pos == SKILLS) 
  {
    skills();
    return;
  }

  //Drive to Goal
  autoDrive(2000, 55);

  //Pick up goal
  FrontArms.spinFor(vex::reverse, 180, degrees);

  //Drive back
  autoDrive(2000, -70);
}

void driver(CarryArmDualMotors fArm, ElevatorArmMotor bArm, ElevatorArmMotor tArm)
{
  leftDriveAxis().changed([](){ powerLeft(leftDriveAxis().position()); });
  rightDriveAxis().changed([](){ powerRight(rightDriveAxis().position()); });

  fArm.update(frontArmsUp().pressing(), frontArmsDown().pressing(), false);
  bArm.update(backArmsUp().pressing(), backArmsDown().pressing(), false);
  tArm.update(tiltArmsUp().pressing(), tiltArmsDown().pressing(), false);
  
  //alignVision().pressed([](){ CustomVisionSensor v(CarryVision, CarryVision__BLUE_GOAL, false); v.alignCarryArm(); });
  //alignBackVision().pressed([](){ alignBack(); });
  
  // testing
  if(autonButton().pressing()) {
    auton(SKILLS);
  }

  wait(100, msec);
}

void teleop()
{
  CarryArmDualMotors fArm(FrontArms, true, false);
  ElevatorArmMotor bArm(CascadeArm, true, false);
  ElevatorArmMotor tArm(TiltArm, true, false);

  while(true) 
  {
    driver(fArm, bArm, tArm); 

    wait(100, msec);
  }
}

void panic()
{
  LeftMotor.stop();
  RightMotor.stop();
  FrontArms.stop();
  CascadeArm.stop();
  TiltArm.stop();
}

void calibrateInertial()
{
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Intertial Sensor");

  Inertial.calibrate();
  wait(500, msec);

  Brain.Screen.clearScreen();
}

void init()
{
  calibrateInertial();

  FrontArms.setVelocity(70, percent);

  CascadeArm.setVelocity(80, percent);
  TiltArm.setVelocity(25, percent);

  FrontArms.setMaxTorque(100, percent);

  CascadeArm.setMaxTorque(50, percent);
  TiltArm.setMaxTorque(80, percent);

  FrontArms.setStopping(hold);
  CascadeArm.setStopping(hold);
  TiltArm.setStopping(hold);

  panicButton().pressed(panic);
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //Init
  init();

  //Competition Stuff
  Competition.drivercontrol(teleop);
  Competition.autonomous([](){ auton(SKILLS); });
}
