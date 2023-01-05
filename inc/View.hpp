#ifndef VIEW_HPP_
#define VIEW_HPP_

#include "GameObject.hpp"
#include "Point2D.hpp"

const int view_maxsize = 20;  // max size of grid array

using namespace std;


class View {
 public:
  View();
  virtual ~View();

 public:
  void Clear();
  void Plot(GameObject* ptr);
  void Draw();

 private:
  int     size;
  double  scale;
  Point2D origin = Point2D(0, 0);
  char    grid[view_maxsize][view_maxsize][2];
  bool    GetSubscripts(int& out_x, int& out_y, Point2D location);
};

#endif
