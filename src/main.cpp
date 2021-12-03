// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDriveMotor       motor         1               
// RightDriveMotor      motor         10              
// ArmMotors            motor_group   20, 3           
// IntakeMotor          motor         4               
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

using namespace vex;

controller::axis leftDriveAxis() { return Controller1.Axis3; }
controller::axis rightDriveAxis() { return Controller1.Axis2; }

controller::button toggleArmsButton() { return Controller1.ButtonA; }

controller::button toggleIntakeButton() { return Controller1.ButtonX; }

controller::button forwardIntakeButton() { return Controller1.ButtonR2; }
controller::button reverseIntakeButton() { return Controller1.ButtonL2; }
controller::button disableIntakeButton() { return Controller1.ButtonX; }

bool armsDown;
bool intakeOn;

void toggleArms()
{
  vex::directionType direction = armsDown ? vex::reverse : vex::forward;
  
  ArmMotors.spinFor(direction, 30, degrees);
}

void forwardIntake()
{
  IntakeMotor.spin(vex::forward);
}

void reverseIntake()
{
  IntakeMotor.spin(vex::reverse);
}

void stopIntake()
{
  IntakeMotor.stop();
}

void toggleIntake()
{
  int velocity = 1;
  bool finished = false;

  vex::directionType direction = intakeOn ? vex::reverse : vex::forward;
  int target = intakeOn ? 0 : 30;

  IntakeMotor.setVelocity(velocity, percent);
  IntakeMotor.spin(direction);

  while(!finished)
  {
    if(intakeOn) velocity--;
    else velocity++;

    if(velocity == 0) IntakeMotor.stop();
    else IntakeMotor.setVelocity(velocity, percent);
    
    wait(50, msec);

    if(velocity == target) finished = true;
  }
}

void control()
{
  //Drive
  leftDriveAxis().changed([](){ powerLeft(leftDriveAxis().position()); });
  rightDriveAxis().changed([](){ powerRight(rightDriveAxis().position()); });

  //Toggle Arms
  toggleArmsButton().pressed(toggleArms);

  //Toggle Intake
  //toggleIntakeButton().pressed(toggleIntake);
  forwardIntakeButton().pressed(forwardIntake);

reverseIntakeButton().pressed(reverseIntake);
disableIntakeButton().pressed(stopIntake);

  //Pause
  wait(100, msec);
}

void autonomous()
{

}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  armsDown = true;

  IntakeMotor.setVelocity(5, percent);

  while(true) { control(); }
}
