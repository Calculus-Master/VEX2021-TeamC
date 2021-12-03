#include "vex.h"

void intake(vex::directionType direction)
{
  IntakeMotor.spin(direction);
}

void disableIntake()
{
  IntakeMotor.stop();
}