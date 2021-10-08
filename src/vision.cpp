#include "vex.h"

void visionAim() {
  int middleScreenX = 316/2;

  //Variable for the center of the spotted object 
  int middleObjectX = Vision11.largestObject.centerX;
  bool linedup = false;

  //turning velocities
  LeftMotor.setVelocity(10, percent);
  RightMotor.setVelocity(10, percent);

  while (linedup == false) {
    Vision11.takeSnapshot(Vision11__RED_SCREWDRIVER);
    //Take photo looking for object
     int objectsSpotted = Vision11.takeSnapshot(Vision11__RED_SCREWDRIVER);
    //If no objects are spotted then end the method
    if (objectsSpotted == 0) {
     return;
    }

    //Too far to the left
    while (middleObjectX < middleScreenX - 5) {
      //Idk how the motor code works to be honest so this probably needs to be fixed
      RightMotor.spinFor(forward, 10, degrees);
    }
    //Too far to the right
    while (middleObjectX > middleScreenX - 5) {
      //Same thing here
      LeftMotor.spinFor(forward, 10, degrees);
    }
    //Middle, finally lined up
    RightMotor.stop();
    LeftMotor.stop();
    linedup = true;

  }


  


}