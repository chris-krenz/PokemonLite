#include "../inc/Point2D.hpp"


// STRUCTORS....................................................................

Point2D::Point2D() {
  x = 0.0;
  y = 0.0;
}

Point2D::Point2D(double in_x, double in_y) {
  x = in_x;
  y = in_y;
}


// NON-MEMBER FUNCTIONS.........................................................

// Get dist between two points (non-member func)
double GetDistanceBetween(const Point2D p1, const Point2D p2) {
  double result = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
  return result;
}


// NON-MEMBER OVERLOADS.........................................................

Point2D operator + (const Point2D& p1, const Vector2D& v1) {
  Point2D result = Point2D(p1.x + v1.x, p1.y + v1.y);
  return result;
}

Vector2D operator - (const Point2D& p1, const Point2D& p2) {
  Vector2D result = Vector2D(p1.x - p2.x, p1.y - p2.y);
  return result;
}

ostream& operator << (ostream& output, const Point2D& p) {
  output << fixed << setprecision(2) << "(" << p.x << ", " << p.y << ")";
  return output;
}
