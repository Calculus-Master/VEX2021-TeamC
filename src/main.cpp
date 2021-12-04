// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   13, 12          
// IntakeMotor          motor         4               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   11, 12          
// IntakeMotor          motor         4               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   11, 12          
// IntakeMotor          motor         4               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
// Vision               vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
// Vision15             vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
// Vision15             vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----
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
#include "lift.h"

using namespace vex;

controller::axis leftDriveAxis() { return Controller1.Axis3; }
controller::axis rightDriveAxis() { return Controller1.Axis2; }

controller::button ArmsButtonUp() { return Controller1.ButtonR1; }
controller::button ArmsButtonDown() { return Controller1.ButtonL1; }

controller::button forwardIntakeButton() { return Controller1.ButtonR2; }
controller::button reverseIntakeButton() { return Controller1.ButtonL2; }
controller::button disableIntakeButton() { return Controller1.ButtonX; }

bool armsDown;

void ArmsUp()
{
  ArmMotors.spinFor(forward, 60, degrees);
}

void ArmsDown()
{
  ArmMotors.spinFor(reverse, 60, degrees);
}

void control()
{
  //Drive
  leftDriveAxis().changed([](){ powerLeft(rightDriveAxis().position()); });
  rightDriveAxis().changed([](){ powerRight(leftDriveAxis().position()); });

  //Toggle Arms
  ArmsButtonUp().pressed(ArmsUp);
  ArmsButtonDown().pressed(ArmsDown);

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

void preciseAlign()
{
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(3, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(4, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.clearLine();

  LeftDriveMotor.setVelocity(90, percent);
  RightDriveMotor.setVelocity(90, percent);

  bool aligned = false;

  int fovX = 316;
  int fovCenter = fovX / 2;
  int ME = 3;

  while(!aligned)
  {
    wait(100, msec);

    Vision.takeSnapshot(Vision__RED_ALLIANCE);

    if(Vision.objectCount == 0)
    {
      Brain.Screen.setCursor(2, 2);
      Brain.Screen.print("No objects");
      return;
    }

    int goal = Vision.objects[0].centerX;

    double offset = fovCenter - goal;
    double goalDistance = 59.0;

    if(abs((int)offset) <= ME) aligned = true;
    else
    {
      double turnAngle = atan(offset / goalDistance);
      if(turnAngle < 0) turnAngle *= -1;

      turnAngle *= 180;
      turnAngle /= 3.1415926;

      Brain.Screen.setCursor(3, 2);
      Brain.Screen.print(offset);
      Brain.Screen.setCursor(4, 2);
      Brain.Screen.print(goalDistance);
      Brain.Screen.setCursor(5, 2);
      Brain.Screen.print(turnAngle);

      if(offset < 0)
      {
        LeftDriveMotor.spinFor(forward, turnAngle, degrees);
        RightDriveMotor.spinFor(reverse, turnAngle, degrees);
      }
      else
      {
        LeftDriveMotor.spinFor(reverse, turnAngle, degrees);
        RightDriveMotor.spinFor(forward, turnAngle, degrees);
      }
    }
  }

 
}

void liftIntake() {
  
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
  //Auton set to 

  //Precise align requires change in color signature each time
  turn(45, vex::right);
  preciseAlign();
  drive(vex::forward, 2000);
 ArmsUp();
 ArmsUp();


}

//Our custom initializations
void init()
{
  armsDown = false;
  IntakeMotor.setVelocity(5, percent);
  ArmMotors.setVelocity(50, percent);
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

//lmao im putting vision in the main
