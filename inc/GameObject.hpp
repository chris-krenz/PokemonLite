#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <iostream>

#include "Point2D.hpp"

using namespace std;


// Abstract Base Class
class GameObject {
 public:
  GameObject(char in_code);
  GameObject(char in_code, int in_id, Point2D in_loc);
  virtual ~GameObject();

  Point2D      GetLocation();
  int          GetID();
  char         GetState();
  virtual void ShowStatus();
  void         DrawSelf(char* ptr);

  virtual bool Update()          = 0;
  virtual bool ShouldBeVisible() = 0;

 protected:
  Point2D location;
  int     id_num;
  char    display_code;
  char    state;
};

#endif
