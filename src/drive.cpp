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