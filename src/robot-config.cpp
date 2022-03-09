#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor HookArmsMotorA = motor(PORT3, ratio18_1, true);
motor HookArmsMotorB = motor(PORT4, ratio18_1, false);
motor_group HookArms = motor_group(HookArmsMotorA, HookArmsMotorB);
/*vex-vision-config:begin*/
signature ElevatorVision__RED_GOAL = signature (1, 7085, 8705, 7895, -999, -465, -732, 3, 0);
vision ElevatorVision = vision (PORT20, 50, ElevatorVision__RED_GOAL);
/*vex-vision-config:end*/
inertial Inertial = inertial(PORT10);
/*vex-vision-config:begin*/
signature CarryVision__RED_GOAL = signature (1, 7451, 9457, 8454, -1065, -353, -710, 3, 0);
signature CarryVision__MIDDLE_GOAL = signature (2, 1515, 2033, 1774, -3687, -3253, -3470, 3.3, 0);
signature CarryVision__BLUE_GOAL = signature (3, -1873, -1451, -1662, 4615, 6707, 5661, 3.5, 0);
vision CarryVision = vision (PORT19, 35, CarryVision__RED_GOAL, CarryVision__MIDDLE_GOAL, CarryVision__BLUE_GOAL);
/*vex-vision-config:end*/
distance Optical = distance(PORT16);
motor CascadeArm = motor(PORT6, ratio18_1, false);
motor TiltArm = motor(PORT5, ratio18_1, false);
motor LeftMotorMotorA = motor(PORT1, ratio18_1, false);
motor LeftMotorMotorB = motor(PORT9, ratio18_1, false);
motor_group LeftMotor = motor_group(LeftMotorMotorA, LeftMotorMotorB);
motor RightMotorMotorA = motor(PORT2, ratio18_1, true);
motor RightMotorMotorB = motor(PORT8, ratio18_1, true);
motor_group RightMotor = motor_group(RightMotorMotorA, RightMotorMotorB);

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