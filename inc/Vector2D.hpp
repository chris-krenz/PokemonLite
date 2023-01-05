#ifndef VECTOR2D_HPP_
#define VECTOR2D_HPP_

#include "math.h"

#include <iostream>
#include <iomanip>

using namespace std;


class Vector2D {
 public:
  double x;
  double y;

  Vector2D();
  Vector2D(double, double);
};

double GetDistanceBetween(const Vector2D v1, const Vector2D v2);
ostream& operator << (ostream&,        const Vector2D&);
Vector2D operator *  (const Vector2D&, const double&);
Vector2D operator /  (const Vector2D&, const double&);

#endif
