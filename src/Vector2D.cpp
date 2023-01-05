#include "../inc/Vector2D.hpp"


// STRUCTORS....................................................................

Vector2D::Vector2D() {
  x = 0.0;
  y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y) {
  x = in_x;
  y = in_y;
}


// NON-MEMBER FUNCTIONS.........................................................

// Get dist between two vectors (non-member func)
double GetDistanceBetween(const Vector2D v1, const Vector2D v2) {
  return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2));
}


// NON-MEMBER OVERLOADS.........................................................

Vector2D operator * (const Vector2D& v, const double& s) {
  return Vector2D(v.x*s, v.y*s);
}

Vector2D operator / (const Vector2D& v, const double& s) {
  if (s == 0) { return v; }
  return Vector2D(v.x/s, v.y/s);
}

ostream& operator << (ostream& output, const Vector2D& v) {
  output << fixed << setprecision(2)
         << "<" << v.x << ", " << v.y << ">";
  return output;
}
