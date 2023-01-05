#ifndef BUILDING_HPP_
#define BUILDING_HPP_

#include <iostream>

#include "GameObject.hpp"

using namespace std;


class Building : public GameObject {
 public:
  Building(char in_code = 'B');
  Building(char in_code, int in_Id, Point2D in_loc);
  virtual ~Building();

  void AddOneTrainer();
  void RemoveOneTrainer();
  void ShowStatus();
  bool ShouldBeVisible();

 private:
  unsigned int trainer_count;
};

#endif
