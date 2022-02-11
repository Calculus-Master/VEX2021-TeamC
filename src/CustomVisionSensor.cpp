#include "vex.h"
#include "CustomVisionSensor.h"
#include <cmath>

//Print Statements
void clearVisionPrintLines()
{
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(3, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(4, 2);
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.clearLine();
}

void printVisionValues(double offset, double goalDistance, double turnAngle)
{
  Brain.Screen.setCursor(3, 2);
  Brain.Screen.print(offset);
  Brain.Screen.setCursor(4, 2);
  Brain.Screen.print(goalDistance);
  Brain.Screen.setCursor(5, 2);
  Brain.Screen.print(turnAngle);
}

void printVisionNoObjects()
{
  Brain.Screen.setCursor(2, 2);
  Brain.Screen.print("No Object Detected!");
  Brain.Screen.setCursor(3, 7);
}

//Alignment
void alignTurnLeft(double angle)
{
  angle = angle > 0 ? angle : -angle;
  LeftMotor.spinFor(vex::reverse, angle, degrees);
  RightMotor.spinFor(vex::forward, angle, degrees);
}

void alignTurnRight(double angle)
{
  angle = angle > 0 ? angle : -angle;
  LeftMotor.spinFor(vex::forward, angle, degrees);
  RightMotor.spinFor(vex::reverse, angle, degrees);
}

void CustomVisionSensor::setAlignmentDriveVelocity()
{
  LeftMotor.setVelocity(visionDriveVelocity, percent);
  RightMotor.setVelocity(visionDriveVelocity, percent);
}

void CustomVisionSensor::visionDriveToNew()
{
  int currentDistance = Optical.objectDistance(mm);

  LeftMotor.spin(forward);
  RightMotor.spin(forward);

  int headstart = 0;
  while(headstart < 25) { wait(100, msec); headstart++; }

  currentDistance = Optical.objectDistance(mm);

  while(currentDistance > 97)
  {
    Brain.Screen.setCursor(4, 4);
    Brain.Screen.print("Driving");

    currentDistance = Optical.objectDistance(mm);

    wait(10, msec);
  }

  LeftMotor.stop();
  RightMotor.stop();
}

//Sensor Position: Center
void CustomVisionSensor::alignElevatorArm()
{
  //Take Snapshot Color: Gray
  v.setLedColor(100, 100, 100);

  clearVisionPrintLines();
  setAlignmentDriveVelocity();

  bool aligned = false;

  //Target: Center of the FOV
  int targetX = visionFOV_X / 2 - 30;

  while(!aligned)
  {
    wait(100, msec);
    //ISSUE: What does this even do bruh
    v.takeSnapshot(sig, 1);

    //Take Snapshot Color: Red
    v.setLedColor(255, 0, 0);

    if(v.objectCount == 0)
    {
      printVisionNoObjects();
      Brain.Screen.print("Elevator Arm");
      return;
    }

    //ISSUE: This is consistently returning 0
    double goal = v.objects[0].centerX;

    double offset = targetX - goal;
    //Goal Distance should be modified for purpose - 59 is to center of field
    double goalDistance = 59.0;

    if(abs((int)offset) <= visionMarginOfError) aligned = true;
    else
    {
      //Take Snapshot Color: Green
      v.setLedColor(0, 255, 0);

      double turnAngle = atan(offset / goalDistance);
      if(turnAngle < 0) turnAngle *= 1;

      turnAngle *= 180;
      turnAngle /= 3.1415926;

      printVisionValues(goal, goalDistance, turnAngle);

      if(offset < 0) alignTurnRight(turnAngle);
      else alignTurnLeft(turnAngle);
    }
  }

  visionDriveTo(vex::reverse);
}

//Sensor Position: Right
void CustomVisionSensor::alignCarryArm()
{
  //Take Snapshot Color: Gray
  v.setLedColor(100, 100, 100);

  //v.setBrightness(30);

  clearVisionPrintLines();
  setAlignmentDriveVelocity();

  bool aligned = false;

  //Target: Slightly Right of the Center of the FOV
  int targetX = 316 / 2;

  while(!aligned)
  {
    wait(100, msec);

    v.takeSnapshot(sig, 1);

    //Take Snapshot Color: Blue
    v.setLedColor(0, 0, 255);

    if(v.objectCount == 0)
    {
      printVisionNoObjects();
      Brain.Screen.print("Carry Arm");
      return;
    }

    int goalCenter = v.objects[0].centerX;

    double offset = targetX - goalCenter;
    offset /= 2;
    double goalDistance = 59.0;

    Brain.Screen.setCursor(6, 6);
    Brain.Screen.print("G");
    Brain.Screen.setCursor(6, 7);
    Brain.Screen.print(goalCenter);
    Brain.Screen.setCursor(6, 8);
    Brain.Screen.print(offset);

    if(abs((int)offset) <= visionMarginOfError) aligned = true;
    else
    {
      //Take Snapshot Color: Green + Blue (whatever color that makes)
      v.setLedColor(0, 255, 255);

      double turnAngle = atan(abs((int)offset) / goalDistance);

      turnAngle *= 180;
      turnAngle /= 3.1415926;

      turnAngle = 10;

      printVisionValues(offset, goalDistance, turnAngle);

      if(offset < 0) alignTurnRight(turnAngle);
      else alignTurnLeft(turnAngle);
    }
  }

  alignTurnRight(60);
}