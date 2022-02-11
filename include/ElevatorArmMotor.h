#include "vex.h"
using namespace vex;


class ElevatorArmMotor {
  public:
  motor ArmMotor;
  bool reverse, stopEnd;

  
  ElevatorArmMotor(motor ArmMotor, bool s, bool reverse): stopEnd(s), reverse(reverse), ArmMotor(ArmMotor) {};
  
  void update(bool bUp, bool bDown, bool bStop);

  private: 
  void up();
  void down();
  void Mstop();
};