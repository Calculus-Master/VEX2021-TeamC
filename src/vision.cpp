#include "vex.h"
#include "vision.h"
#include <iostream>

int count = 0;
void visionAim() {
  count++;
    Brain.Screen.setCursor(2, 3);
     Brain.Screen.print(count);

  int middleScreenX = 316/2;

  //Variable for the center of the spotted object 
  bool linedup = false;

  //turning velocities
  LeftMotor.setVelocity(10, percent);
  RightMotor.setVelocity(10, percent);

  while (linedup == false) {
    Vision.takeSnapshot(Vision__GOAL);
    //Take photo looking for object
     int objectsSpotted = Vision.objectCount;
     Brain.Screen.setCursor(3, 3);
     Brain.Screen.print(objectsSpotted);
     
    if (objectsSpotted == 0) {
      linedup = true;
     return;
    }

    Brain.Screen.setCursor(4, 3);
     Brain.Screen.print(Vision.objects[0].centerX);
     Brain.Screen.setCursor(5, 3);
     Brain.Screen.print(middleScreenX);
    //Declare value for the middle of the object
    int middleObjectX = Vision.largestObject.centerX;

    //Too far to the left
    // if (middleObjectX < middleScreenX - 5) {
    //   //Idk how the motor code works to be honest so this probably needs to be fixed. Right now the turn value
    //   //is very slow. 
    //   RightMotor.spinFor(forward, 10, degrees);
    // }
    // //Too far to the right
    // else if (middleObjectX > middleScreenX - 5) {
    //   //Same thing here
    //   LeftMotor.spinFor(forward, 10, degrees);
    // }
    
    // //Middle, finally lined up
    // else {
    // RightMotor.stop();
    // LeftMotor.stop();
    // linedup = true;
    // }

    wait(100, msec);
    linedup = true;
  }
}

void betterVision()
{
  LeftMotor.setVelocity(50, percent);
  RightMotor.setVelocity(50, percent);
  bool aligned = false;
  int middle = 316 / 2; 

  while(!aligned)
  {
    Vision.takeSnapshot(Vision__GOAL);

    Brain.Screen.setCursor(2, 3);

    if(Vision.objectCount == 0)
    {
      Brain.Screen.print("No objects");
      return;
    }
    else Brain.Screen.print("Objects");
    
    int targetX = Vision.objects[0].centerX;
    if(targetX > middle + 10) 
    {
      LeftMotor.spinFor(forward, 10, degrees);
      RightMotor.spinFor(reverse, 10, degrees);
    }
    else if(targetX < middle - 10) 
    {
      LeftMotor.spinFor(reverse, 10, degrees);
     RightMotor.spinFor(forward, 10, degrees);
    }
    else aligned = true;
  }
  Brain.Screen.clearLine();

  //In Main
  //while(true) { align(); wait(5, msec)}
}