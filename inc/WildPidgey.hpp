#ifndef WILDPIDGEY_HPP_
#define WILDPIDGEY_HPP_

#include <time.h>
#include <math.h>

#include <iostream>
#include <string>

#include "WildPokemon.hpp"

#include "GameObject.hpp"
#include "Point2D.hpp"
#include "Trainer.hpp"
#include "View.hpp"

using namespace std;


class WildPidgey : public WildPokemon {
 public:
  WildPidgey(string in_name, double in_attack, double in_health, bool in_variant,
             int in_id, Point2D in_loc, char in_code = 'P');
  virtual ~WildPidgey();

  bool get_perching  ();
  void set_perching  (bool if_perching);
  void set_perch_num (int num_buildings);
  void set_perch     (Building* b);

  virtual void follow(Trainer* t);

  void ShowStatus();

 private:
  int  max_perch_time;
  int  perch_time;
  int  perch_num;                              // Model sets to num of buildings
  bool perching;

  Building* current_building = NULL;

};

#endif
