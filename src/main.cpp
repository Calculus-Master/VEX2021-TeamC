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
// BackArms             motor_group   5, 6            
// BackVision           vision        20              
// Inertial             inertial      10              
// FrontVision          vision        19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

controller::axis leftDriveAxis() { return Controller1.Axis3; }
controller::axis rightDriveAxis() { return Controller1.Axis2; }

controller::button frontArmsUp() { return Controller1.ButtonR1; }
controller::button frontArmsDown() { return Controller1.ButtonL1; }

controller::button backArmsUp() { return Controller1.ButtonR2; }
controller::button backArmsDown() { return Controller1.ButtonL2; }

controller::button alignBackVision() { return Controller1.ButtonDown; }
controller::button alignFrontVision() { return Controller1.ButtonUp; }

int deadzone = 5;
int minimumDriveVelocity = 20;

//Vision
void alignIfCenter()
{
  vex::vision v = BackVision;
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(3, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(4, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.clearLine();

  LeftMotor.setVelocity(90, percent);
  RightMotor.setVelocity(90, percent);

  bool aligned = false;

  int fovX = 316;
  int fovCenter = fovX / 2;
  int ME = 3;

  while(!aligned)
  {
    wait(100, msec);

    v.takeSnapshot(FrontVision__RED_GOAL);

    if(v.objectCount == 0)
    {
      Brain.Screen.setCursor(2, 2);
      Brain.Screen.print("No objects");
      return;
    }

    int goal = v.objects[0].centerX;

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
        LeftMotor.spinFor(forward, turnAngle, degrees);
        RightMotor.spinFor(reverse, turnAngle, degrees);
      }
      else
      {
        LeftMotor.spinFor(reverse, turnAngle, degrees);
        RightMotor.spinFor(forward, turnAngle, degrees);
      }
    }
  }
}

void alignIfRight()
{
  vex::vision v = FrontVision;
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(3, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(4, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.clearLine();

  LeftMotor.setVelocity(90, percent);
  RightMotor.setVelocity(90, percent);

  bool aligned = false;

  int fovX = 316;
  int fovCenter = fovX / 2;
  int ME = 3;

  fovCenter += 100;

  while(!aligned)
  {
    wait(100, msec);

    v.takeSnapshot(FrontVision__RED_GOAL);

    if(v.objectCount == 0)
    {
      Brain.Screen.setCursor(2, 2);
      Brain.Screen.print("No objects");
      return;
    }

    int goalCenter = v.objects[0].centerX;

    double offset = fovCenter - goalCenter;
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
        LeftMotor.spinFor(forward, turnAngle, degrees);
        RightMotor.spinFor(reverse, turnAngle, degrees);
      }
      else
      {
        LeftMotor.spinFor(reverse, turnAngle, degrees);
        RightMotor.spinFor(forward, turnAngle, degrees);
      }
    }
  }
}

//Back Arms
void moveBackArms(vex::directionType direction)
{
  BackArms.spin(direction);
}

void stopBackArms()
{
  BackArms.stop();
}

//Front Arms
void moveFrontArms(vex::directionType direction)
{
  FrontArms.spin(direction);
}

void stopFrontArms()
{
  FrontArms.stop();
}

//Driving
int velocityAt(int position)
{
  int absPos = std::abs(position);

  return absPos < minimumDriveVelocity ? minimumDriveVelocity : absPos;
}

void powerLeft(int position)
{
  if(position >= -1 * deadzone && position <= deadzone) LeftMotor.stop();
  else
  {
    vex::directionType direction = position < 0 ? vex::reverse : vex::forward;

    LeftMotor.setVelocity(velocityAt(position), percent);
    LeftMotor.spin(direction);
  }
}

void powerRight(int position)
{
  if(position >= -1 * deadzone && position <= deadzone) RightMotor.stop();
  else
  {
    vex::directionType direction = position < 0 ? vex::reverse : vex::forward;

    RightMotor.setVelocity(std::abs(position), percent);
    RightMotor.spin(direction);
  }
}

bool checkMotorTemps()
{
  int tempLimit = 60;
  vex::temperatureUnits c = vex::temperatureUnits::celsius;

  bool exit = false;

  //Check Drive Motors (These shouldn't overheat)
  if(LeftMotor.temperature(c) > tempLimit || LeftMotor.temperature(c) > tempLimit)
  {
    Brain.Screen.setCursor(2, 2);
    Brain.Screen.clearLine();
    Brain.Screen.print("Drive Motor Overheated!");

    Brain.Screen.setCursor(3, 3);
    Brain.Screen.print(LeftMotor.temperature(c));
    Brain.Screen.setCursor(3, 4);
    Brain.Screen.print(RightMotor.temperature(c));

    exit = true;
  }

  //Check Back Arm Motors (These shouldn't really overheat)
  if(BackArms.temperature(c) > tempLimit)
  {
    Brain.Screen.setCursor(3, 2);
    Brain.Screen.clearLine();
    Brain.Screen.print("Back Arm Motors (Longer Arms) Overheated!");

    Brain.Screen.setCursor(3, 3);
    Brain.Screen.print(BackArms.temperature(c));

    exit = true;
  }

  //Check Front Arm Motors (These will most likely overheat)
  if(FrontArms.temperature(c) > tempLimit)
  {
    Brain.Screen.setCursor(4, 2);
    Brain.Screen.clearLine();
    Brain.Screen.print("Front Arm Motors (Shorter Arms) Overheated!");

    Brain.Screen.setCursor(4, 3);
    Brain.Screen.print(FrontArms.temperature(c));

    exit = true;
  }

  return exit;
}

void driver()
{
  leftDriveAxis().changed([](){ powerLeft(leftDriveAxis().position()); });
  rightDriveAxis().changed([](){ powerRight(rightDriveAxis().position()); });

  frontArmsUp().pressed([](){ moveFrontArms(vex::forward); });
  frontArmsDown().pressed([](){ moveFrontArms(vex::reverse); });

  if(frontArmsUp().pressing()) moveFrontArms(vex::forward);
  else if(frontArmsDown().pressing()) moveFrontArms(vex::reverse);
  else stopFrontArms();

  if(backArmsUp().pressing()) moveBackArms(vex::forward);
  else if(backArmsDown().pressing()) moveBackArms(vex::reverse);
  else stopBackArms();

  alignFrontVision().pressed([](){ alignIfRight(); });
  alignBackVision().pressed([](){ alignIfCenter(); });

  wait(100, msec);
}

void auton()
{

}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating Intertial Sensor");

  Inertial.calibrate();
  wait(2, seconds);
  
  Brain.Screen.clearScreen();

  FrontArms.setVelocity(70, percent);
  BackArms.setVelocity(80, percent);

  FrontArms.setMaxTorque(100, percent);
  BackArms.setMaxTorque(50, percent);

  FrontArms.setStopping(hold);
  BackArms.setStopping(hold);

  while(true) 
  {
    driver(); 

    if(checkMotorTemps()) break;
  }
}
