#include "vex.h"
#include "util.h"

void drive(vex::directionType direction)
{
  LeftMotor.spin(direction);
  RightMotor.spin(direction);
}

void turn(vex::turnType direction)
{
  vex::directionType dir = direction == right ? vex::forward : vex::reverse;

  LeftMotor.spin(dir);
  RightMotor.spin(flip(dir));
}

void setVelocity(int value)
{
  LeftMotor.setVelocity(value, vex::percent);
  RightMotor.setVelocity(value, vex::percent);
}