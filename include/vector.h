class Vec2d {
  private:
	double x;
  double y;
  double magnitiude;
  public: 
  Vec2d (double newX, double newY);
  Vec2d (double mag, double newAngle, bool useMag );
  double getX();
  double getY();
  double getMag();
  void setX(double newX);
  void setY(double newY);
  double getAngle();
  Vec2d rotate(double newAngle);
  Vec2d setAngle (double newAngle);
  Vec2d setMag(double newMag);


  ~Vec2d();
};

double vecAngle(Vec2d a, Vec2d b);

void driveAngle(double turnAngle);

void driveVec (Vec2d, bool);

double mod (double a, double b);