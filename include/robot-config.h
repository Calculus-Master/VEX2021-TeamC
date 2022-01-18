using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor LeftMotor;
extern motor RightMotor;
extern motor_group FrontArms;
extern motor_group BackArms;
extern signature BackVision__RED_GOAL;
extern signature BackVision__SIG_2;
extern signature BackVision__SIG_3;
extern signature BackVision__SIG_4;
extern signature BackVision__SIG_5;
extern signature BackVision__SIG_6;
extern signature BackVision__SIG_7;
extern vision BackVision;
extern inertial Inertial;
extern signature FrontVision__RED_GOAL;
extern signature FrontVision__SIG_2;
extern signature FrontVision__SIG_3;
extern signature FrontVision__SIG_4;
extern signature FrontVision__SIG_5;
extern signature FrontVision__SIG_6;
extern signature FrontVision__SIG_7;
extern vision FrontVision;
extern distance Optical;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );