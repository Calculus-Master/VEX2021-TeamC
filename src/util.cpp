#include "vex.h"

vex::directionType flip(vex::directionType direction)
{
  return direction == vex::forward ? vex::reverse : vex::forward;
}

vex::turnType flip(vex::turnType direction)
{
  return direction == vex::right ? vex::left : vex::right;
}