#include "vex.h"
#include <cmath>

class CustomVisionSensor {
  public:

  CustomVisionSensor(vex::vision v, signature s, bool f) : v(v), isFront(f), sig(s) {};

  void align();
  void visionDriveToNew();
  void setAlignmentDriveVelocity();
  void visionDriveTo(vex::directionType dir);
  void alignCarryArm();
  void alignElevatorArm();


  inline signature getSig() const { return sig; }

  private:

  const int visionDriveVelocity = 90;
  const int visionFOV_X = 316;
  const int visionMarginOfError = 10;

  signature sig;

  vision v;

  bool isFront;
  
  
};