using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor_group HookArms;
extern signature ElevatorVision__RED_GOAL;
extern signature ElevatorVision__SIG_2;
extern signature ElevatorVision__SIG_3;
extern signature ElevatorVision__SIG_4;
extern signature ElevatorVision__SIG_5;
extern signature ElevatorVision__SIG_6;
extern signature ElevatorVision__SIG_7;
extern vision ElevatorVision;
extern inertial Inertial;
extern signature CarryVision__RED_GOAL;
extern signature CarryVision__MIDDLE_GOAL;
extern signature CarryVision__BLUE_GOAL;
extern signature CarryVision__SIG_4;
extern signature CarryVision__SIG_5;
extern signature CarryVision__SIG_6;
extern signature CarryVision__SIG_7;
extern vision CarryVision;
extern distance Optical;
extern motor CascadeArm;
extern motor TiltArm;
extern motor_group LeftMotor;
extern motor_group RightMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );