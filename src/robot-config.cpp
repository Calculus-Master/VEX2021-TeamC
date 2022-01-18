#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftMotor = motor(PORT2, ratio36_1, false);
motor RightMotor = motor(PORT1, ratio36_1, true);
motor FrontArmsMotorA = motor(PORT3, ratio18_1, true);
motor FrontArmsMotorB = motor(PORT4, ratio18_1, false);
motor_group FrontArms = motor_group(FrontArmsMotorA, FrontArmsMotorB);
motor BackArmsMotorA = motor(PORT5, ratio18_1, false);
motor BackArmsMotorB = motor(PORT6, ratio18_1, true);
motor_group BackArms = motor_group(BackArmsMotorA, BackArmsMotorB);
/*vex-vision-config:begin*/
signature BackVision__RED_GOAL = signature (1, 7085, 8705, 7895, -999, -465, -732, 3, 0);
vision BackVision = vision (PORT20, 50, BackVision__RED_GOAL);
/*vex-vision-config:end*/
inertial Inertial = inertial(PORT10);
/*vex-vision-config:begin*/
signature FrontVision__RED_GOAL = signature (1, 6319, 8193, 7256, -917, 355, -282, 3, 0);
vision FrontVision = vision (PORT19, 50, FrontVision__RED_GOAL);
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