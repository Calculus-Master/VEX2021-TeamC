#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor = motor(PORT10, ratio18_1, false);
motor RightMotor = motor(PORT1, ratio18_1, false);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
signature Vision__GOAL = signature (1, 1433, 1947, 1690, -3121, -2497, -2809, 3, 0);
signature Vision__RING = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision = vision (PORT9, 50, Vision__GOAL, Vision__RING);
/*vex-vision-config:end*/
motor forkLiftMotor = motor(PORT2, ratio36_1, false);
inertial Gyro = inertial(PORT6);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}