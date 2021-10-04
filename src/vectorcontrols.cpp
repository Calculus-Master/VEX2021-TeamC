#include <cmath>

double π =  2 * acos (0.0);

class Vector2D
{
  private:

    double x;
    double y;
    double magnitude;

  public:

      Vector2D (double x, double y)
      {
        this->x = x;
        this->y = y;
        magnitude = sqrt (pow (x, 2) + pow (y, 2));
      }

      Vector2D (double mag, double newAngle, bool useMag) 
      {
        x = useMag ? cos (newAngle) * mag : cos (newAngle);
        y = useMag ? sin (newAngle) * mag : sin (newAngle);
        magnitude = useMag ? mag : 1.0;
      }

      void setMagnitude()
      {
        this->magnitude = sqrt(pow(x, 2) + pow(y,2));
      }

      double getMagnitude()
      {
        return magnitude;
      }

      double getX () { return x; }

      double getY() { return y; }

      void setX(double x)
      {
        this->x = x;
        this->setMagnitude(); 
      }

      void setY(double y)
      {
        this->y = y;
        this->setMagnitude(); 
      }

      double getAngle()
      {
        return atan(y / x);
      }

      void rotate(double angle)
      {
        double target = this->getAngle() + angle;
        target = mod(target, π * 2);

        x = cos(target) * this->getMagnitude();
        y = cos(target) * this->getMagnitude();

        this->setMagnitude();
      }

      void setMagnitude(double magnitude)
      {
        double angle = this->getAngle();

        x = cos(angle) * magnitude;
        y = sin(angle) * magnitude;

        this->magnitude = magnitude;
      }

      double mod(double a, double b)
      {
        return fmod(a, b);
      }
};


// input order matters

double vecAngle (Vector2D a, Vector2D b)

{

  return a.getAngle () - b.getAngle ();

}


// void driveAngle (double turnAngle)

// {

//   double angle1 = Rotation2.angle () - (turnAngle * 180 / (2 * pi));

//   double newTurnAngle = std::abs (angle1) * 180 / (2 * pi);

//   if (newTurnAngle == angle1)

//     {

//       //Drivetrain.turnFor (left, newTurnAngle, degrees);

//     }

//   else

//     {

//       //Drivetrain.turnFor (right, newTurnAngle, degrees);

//     }

// }


// void driveVec (Vector2D vector)

// {

//   driveAngle (vector.getAngle ());

//   //Drivetrain.drive (vector.getMag ());

// }