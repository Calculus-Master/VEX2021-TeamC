// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         10              
// RightMotor           motor         1               
// Controller1          controller                    
// Vision               vision        9               
// forkLiftMotor        motor         2               
// Gyro                 inertial      6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         10              
// RightMotor           motor         1               
// Controller1          controller                    
// Vision               vision        9               
// forkLiftMotor        motor         2               
// Gyro                 inertial      6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         10              
// RightMotor           motor         1               
// Controller1          controller                    
// Vision               vision        3               
// forkLiftMotor        motor         2               
// Gyro                 inertial      6               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         10              
// RightMotor           motor         1               
// Controller1          controller                    
// Vision               vision        3               
// forkLiftMotor        motor         2               
// Gyro                 inertial      6               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       saptarshimallick                                          */
/*    Created:      Mon Sep 20 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include "singleaxiscontrols.h"
#include "tankcontrols.h"
#include "vision.h"
#include <iostream>

using namespace vex;
using namespace std;

void align()
{
  LeftMotor.setVelocity(100, percent);
  RightMotor.setVelocity(100, percent);
  bool aligned = false;
  int fovX = 316;
  int middle = fovX / 2; 
  int ME = 8;
  int deg = 15;

  while(!aligned)
  {

    Vision.takeSnapshot(Vision__GOAL);

    Brain.Screen.setCursor(2, 3);

    if(Vision.objectCount == 0)
    {
      Brain.Screen.print("No objects");
      return;
    }
    else Brain.Screen.print("Objects");

    int targetX = Vision.objects[0].centerX;
    if(targetX > middle + ME) 
    {
      LeftMotor.spinFor(forward, deg, degrees);
      RightMotor.spinFor(reverse, deg, degrees);
    }
    else if(targetX < middle - ME) 
    {
      LeftMotor.spinFor(reverse, deg, degrees);
     RightMotor.spinFor(forward, deg, degrees);
    }
    else aligned = true;
  }

  Brain.Screen.clearLine();

  wait(500, msec);

  Brain.Screen.setCursor(3, 3);
  Brain.Screen.print("Driving to Object");

  bool reached = false;

  RightMotor.setVelocity(20, percent);
  LeftMotor.setVelocity(20, percent);

  LeftMotor.spin(forward);
  RightMotor.spin(forward);

  while(!reached)
  {
    Vision.takeSnapshot(Vision__GOAL);

    int targetSize = Vision.objects[0].width;

    if(targetSize > 0.9 * fovX) reached = true;
  }

  LeftMotor.stop();
  RightMotor.stop();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(true)
  {
    Controller1.ButtonA.pressed(align);
    //Controller1.ButtonB.pressed(driveTo);
  }
}

//Controls
controller::axis axisLeft() { return Controller1.Axis3; }
controller::axis axisRight() { return Controller1.Axis2; }

controller::button visioning() { return Controller1.ButtonB; }

void betterVision()
{
  LeftMotor.setVelocity(50, percent);
  RightMotor.setVelocity(50, percent);
  bool aligned = false;
  int middle = 316 / 2; 

  while(!aligned)
  {
    Vision.takeSnapshot(Vision__GOAL);

    Brain.Screen.setCursor(2, 3);

    if(Vision.objectCount == 0)
    {
      Brain.Screen.print("No objects");
      return;
    }
    else Brain.Screen.print("Objects");
    
    int targetX = Vision.objects[0].centerX;
    if(targetX > middle + 10) 
    {
      LeftMotor.spinFor(vex::forward, 10, degrees);
      RightMotor.spinFor(reverse, 10, degrees);
    }
    else if(targetX < middle - 10) 
    {
      LeftMotor.spinFor(reverse, 10, degrees);
     RightMotor.spinFor(vex::forward, 10, degrees);
    }
    else aligned = true;
  }
  Brain.Screen.clearLine();

  //In Main
  //while(true) { align(); wait(5, msec)}
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true)
  {
    //axisLeft().changed([](){ powerLeft(axisLeft().position()); });
    //axisRight().changed([](){ powerRight(axisRight().position()); });
    //visioning().pressed([](){ visionAim(); });

    betterVision();
    wait(1000, msec);
    Brain.Screen.clearScreen();
  }
}


