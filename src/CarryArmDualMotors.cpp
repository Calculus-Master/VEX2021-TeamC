#include "CarryArmDualMotors.h"

void CarryArmDualMotors::up() {
  Motors.spin(reverse ? vex::forward : vex::reverse);
}

void CarryArmDualMotors::down() {
  Motors.spin(!reverse ? vex::forward : vex::reverse);
}
void CarryArmDualMotors::Mstop(){
  Motors.stop();
}
void CarryArmDualMotors::update(bool bUp, bool bDown, bool bStop) {
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