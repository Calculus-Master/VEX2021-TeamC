#include "vex.h"

static int deadzone = 5;

void powerLeft(int pos)
{
  vex::directionType direction = pos < 0 ? vex::reverse : vex::forward;

  if(pos < deadzone * -1 || pos > deadzone)
  {
    int velocity = pos < 0 ? pos * -1 : pos;

    LeftDriveMotor.setVelocity(velocity, vex::percent);
    LeftDriveMotor.spin(direction);
  }
  else LeftDriveMotor.stop();
}

void powerRight(int pos)
{
  vex::directionType direction = pos < 0 ? vex::reverse : vex::forward;

  if(pos < deadzone * -1 || pos > deadzone)
  {
    int velocity = pos < 0 ? pos * -1 : pos;

    RightDriveMotor.setVelocity(velocity, vex::percent);
    RightDriveMotor.spin(direction);
  }
  else RightDriveMotor.stop();
}

void powerOff()
{
  LeftDriveMotor.stop();
  RightDriveMotor.stop();
}

//Autonomous

void setVelocity(int velocity)
{
  LeftDriveMotor.setVelocity(velocity, percent);
  RightDriveMotor.setVelocity(velocity, percent);
}

void drive(vex::directionType direction)
{
  LeftDriveMotor.spin(direction);
  RightDriveMotor.spin(direction);
}

void drive(vex::directionType direction, int time)
{
  drive(direction);

  wait(time, msec);

  powerOff();
}

void turn(int deg, vex::turnType direction)
{
  LeftDriveMotor.spinFor(direction == vex::right ? vex::forward : vex::reverse, deg, degrees);
  RightDriveMotor.spinFor(direction == vex::right ? vex::reverse : vex::forward, deg, degrees);
}