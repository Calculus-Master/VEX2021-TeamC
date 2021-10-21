#include "vex.h"
#include "vision.h"

void visionAim() {
  int middleScreenX = 316/2;

  //Variable for the center of the spotted object 
  bool linedup = false;

  //turning velocities
  LeftMotor.setVelocity(10, percent);
  RightMotor.setVelocity(10, percent);

  while (linedup == false) {
    Vision.takeSnapshot(Vision__RED_SCREWDRIVER);
    //Take photo looking for object
     int objectsSpotted = Vision.takeSnapshot(Vision__RED_SCREWDRIVER);
    //If no objects are spotted then end the method
    if (objectsSpotted == 0) {
      linedup = true;
     return;
    }
    //Declare value for the middle of the object
    int middleObjectX = Vision.largestObject.centerX;

    //Too far to the left
    if (middleObjectX < middleScreenX - 5) {
      //Idk how the motor code works to be honest so this probably needs to be fixed. Right now the turn value
      //is very slow. 
      RightMotor.spinFor(forward, 10, degrees);
    }
    //Too far to the right
    else if (middleObjectX > middleScreenX - 5) {
      //Same thing here
      LeftMotor.spinFor(forward, 10, degrees);
    }
    
    //Middle, finally lined up
    else {
    RightMotor.stop();
    LeftMotor.stop();
    linedup = true;
    }

  }


  


}