#include "Drive.h"
#include "vex.h"
#include <cmath>

using namespace std;

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