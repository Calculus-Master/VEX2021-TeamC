using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor LeftDriveMotor;
extern motor RightDriveMotor;
extern motor_group ArmMotors;
extern motor IntakeMotor;
extern signature Vision__RED_ALLIANCE;
extern signature Vision__BLUE_ALLIANCE;
extern signature Vision__MOBILE_GOAL;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );