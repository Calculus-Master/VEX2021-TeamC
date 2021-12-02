using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftDriveMotor;
extern motor RightDriveMotor;
extern motor_group ArmMotors;
extern motor IntakeMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );