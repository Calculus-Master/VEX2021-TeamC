#include <cmath>
#include "vector.h"
#include "vex.h"

extern const double pi = 2*acos(0.0);;
// class Vec2d
// constructors and destructors
Vec2d::Vec2d (double newX, double newY) {
  x = newX;
  y = newY;
  magnitiude = sqrt(pow(x,2) + pow(y,2));
}
  
Vec2d::Vec2d(double mag, double newAngle, bool useMag ) {
  x = useMag ? cos(newAngle) * mag : cos(newAngle);
  y = useMag ? sin(newAngle) * mag : sin(newAngle);
  magnitiude = useMag ? mag : 1.0;
}
  
Vec2d::~Vec2d(){
   
};

// functions
// getters
double Vec2d::getX() {
  return x;
}

double Vec2d::getY() {
  return y;
}

double Vec2d::getAngle() {
  return tan(y/x);
}

double Vec2d::getMag () {
  return magnitiude;
}

// setters
void Vec2d::setX(double newX) {
  x = newX;
  magnitiude = sqrt(pow(x,2) + pow(y,2));
}

void Vec2d::setY(double newY) {
  y = newY;
  magnitiude = sqrt(pow(x,2) + pow(y,2));
}

Vec2d Vec2d::setAngle (double newAngle) {
  double angle = newAngle;
  angle = mod(angle, (pi*2));
  double mag = getMag();
  x = cos(angle) * mag;
  y = sin(angle) * mag;
  return *this;
}

Vec2d Vec2d::setMag (double newMag) {
  double angle = getAngle();
  x = cos(angle) * newMag;
  y = sin(angle) * newMag;
  magnitiude = newMag;
  return *this;
}

// other functions
Vec2d Vec2d::rotate (double newAngle) {
  double angle = getAngle() + newAngle;
  angle = mod(angle, (pi*2));
  double mag = getMag();
  x = cos(angle) * mag;
  y = sin(angle) * mag;
  return *this;
}
// end class

// various functions

// finds difference in angles of two vectors
double vecAngle(Vec2d a, Vec2d b) {
  return a.getAngle() - b.getAngle();
}

// turns to an angle
void driveAngle(double turnAngle) {
  double angle1 = Rotation2.angle() - (turnAngle * 180 / (2 *pi));
  double newTurnAngle = std::abs(angle1) * 180 / (2 *pi);
  
  //may need to flip this, it is not tested
  if (newTurnAngle == angle1) {
    Drivetrain.turnFor(vex::left, newTurnAngle, degrees);
  } else {
      Drivetrain.turnFor(vex::right, newTurnAngle, degrees);
  }
}

// turns to an angle and then drives to it
// set blockProgram to not block the program until the movement has completed
void driveVec(Vec2d vector, bool blockProgram ) {
  driveAngle(vector.getAngle());
  double mag = vector.getMag();
  if (std::signbit(mag)) {
    Drivetrain.driveFor(forward, mag, inches);
  } else {
    Drivetrain.driveFor(reverse, mag, inches);
  } 
}

// utility
// mod but for doubles
double mod (double a, double b) {
  return fmod(a,b);
}