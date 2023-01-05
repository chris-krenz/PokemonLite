#ifndef POINT2D_HPP_
#define POINT2D_HPP_

#include "math.h"

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Vector2D.hpp"

using namespace std;


class Point2D {
 public:
  Point2D();
  Point2D(double, double);

  double x;
  double y;
};

double GetDistanceBetween(const Point2D, const Point2D);
ostream& operator << (ostream&,       const Point2D&);
Point2D  operator +  (const Point2D&, const Vector2D&);
Vector2D operator -  (const Point2D&, const Point2D&);

#endif
