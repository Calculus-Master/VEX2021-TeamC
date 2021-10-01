#include "vex.h"

void powerLeft(int position)
{
  LeftMotor.setVelocity(position < 0 ? position * -1 : position, percent);

  if(position == 0) LeftMotor.stop();
  else LeftMotor.spin(position > 0 ? vex::forward : vex::reverse);
}

void powerRight(int position)
{
  RightMotor.setVelocity(position < 0 ? position * -1 : position, percent);

  if(position == 0) RightMotor.stop();
  else RightMotor.spin(position < 0 ? vex::forward : vex::reverse);
}