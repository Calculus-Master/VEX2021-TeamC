#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftDriveMotor = motor(PORT1, ratio18_1, true);
motor RightDriveMotor = motor(PORT10, ratio18_1, false);
motor ArmMotorsMotorA = motor(PORT13, ratio18_1, false);
motor ArmMotorsMotorB = motor(PORT12, ratio18_1, true);
motor_group ArmMotors = motor_group(ArmMotorsMotorA, ArmMotorsMotorB);
motor IntakeMotor = motor(PORT4, ratio18_1, true);
/*vex-vision-config:begin*/
signature Vision__RED_ALLIANCE = signature (1, 4089, 10717, 7403, -1923, -1465, -1694, 1.6, 0);
signature Vision__BLUE_ALLIANCE = signature (2, -2831, -1331, -2081, 5837, 12289, 9063, 1.3, 0);
signature Vision__MOBILE_GOAL = signature (3, -1, 3067, 1533, -5269, -3875, -4572, 1.8, 0);
vision Vision = vision (PORT15, 50, Vision__RED_ALLIANCE, Vision__BLUE_ALLIANCE, Vision__MOBILE_GOAL);
/*vex-vision-config:end*/

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