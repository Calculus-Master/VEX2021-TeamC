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

bool armsDown;
bool intakeOn;

void toggleArms()
{
  vex::directionType direction = armsDown ? vex::reverse : vex::forward;
  
  ArmMotors.spinFor(direction, 30, degrees);
}

void toggleIntake()
{
  int velocity = 1;
  bool finished = false;

  vex::directionType direction = intakeOn ? vex::reverse : vex::forward;
  int target = intakeOn ? 0 : 75;

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
  toggleIntakeButton().pressed(toggleIntake);

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

  while(true) { control(); }
}
