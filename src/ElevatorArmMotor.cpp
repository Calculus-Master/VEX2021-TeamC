#include "ElevatorArmMotor.h"

void ElevatorArmMotor::up() {
    ArmMotor.spin(reverse ? vex::forward : vex::reverse);
}
void ElevatorArmMotor::down() {
    ArmMotor.spin(!reverse ? vex::forward : vex::reverse);
}
void ElevatorArmMotor::Mstop(){
    ArmMotor.stop();
}
void ElevatorArmMotor::update(bool bUp, bool bDown, bool bStop) {
  if(bUp) {
    up();
  } else if(bDown) {
    down();
  } else if(!stopEnd && bStop) {
    Mstop();
  } else if(stopEnd) {
    Mstop();
  }


}