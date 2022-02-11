#include "vex.h"
using namespace vex;

class CarryArmDualMotors {
  public:
  motor_group Motors;
  bool reverse, stopEnd;

  CarryArmDualMotors(motor_group ArmMotor2, bool s, bool reverse): stopEnd(s), reverse(reverse), Motors(ArmMotor2) {};
  
  void update(bool bUp, bool bDown, bool bStop);

  private: 
  void up();
  void down();
  void Mstop();
};