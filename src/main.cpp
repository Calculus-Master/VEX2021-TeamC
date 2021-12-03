/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       saptarshimallick                                          */
/*    Created:      Thu Dec 02 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   2, 3            
// IntakeMotor          motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "drive.h"
#include "intake.h"

using namespace vex;

controller::axis leftDriveAxis() { return Controller1.Axis3; }
controller::axis rightDriveAxis() { return Controller1.Axis2; }

controller::button toggleArmsButton() { return Controller1.ButtonA; }

controller::button forwardIntakeButton() { return Controller1.ButtonR2; }
controller::button reverseIntakeButton() { return Controller1.ButtonL2; }
controller::button disableIntakeButton() { return Controller1.ButtonX; }

bool armsDown;

void toggleArms()
{
  vex::directionType direction = armsDown ? vex::reverse : vex::forward;
  
  ArmMotors.spinFor(direction, 30, degrees);
}

void control()
{
  //Drive
  leftDriveAxis().changed([](){ powerLeft(leftDriveAxis().position()); });
  rightDriveAxis().changed([](){ powerRight(rightDriveAxis().position()); });

  //Toggle Arms
  toggleArmsButton().pressed(toggleArms);

  //Toggle Intake
  forwardIntakeButton().pressed([](){ intake(vex::forward); });
  reverseIntakeButton().pressed([](){ intake(vex::reverse); });
  disableIntakeButton().pressed(disableIntake);

  //Pause
  wait(100, msec);
}

void manual()
{
  while(true) { control(); }
}

void autonomous()
{
  //Examples of how to do certain things (not a functional autonomous routine!)

  //Drive forward:
  //drive(vex::forward);

  //Drive backward:
  //drive(vex::reverse);

  //Drive a certain time (milliseconds) - I didn't code drive a distance because that requires some more complicated math and physics:
  //drive(vex::forward, 1000);

  //Turn a specific amount:
  //turn(60, vex::left);

  //Temporary stuff
  drive(vex::forward, 3000);
}

//Our custom initializations
void init()
{
  armsDown = true;
  IntakeMotor.setVelocity(5, percent);
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //Any of our Init
  init();

  //Competition Code! (Required during Competition)
  vex::competition c;
  c.autonomous(autonomous);
  c.drivercontrol(manual);

  //If you need to do testing, make sure to start "Timed Run" in the Controller instead of "Run"
  //Timed Run does 15 seconds of autonomous and then the rest in teleop
}
