#ifndef WILDPOKEMON_HPP_
#define WILDPOKEMON_HPP_

#include <time.h>
#include <math.h>

#include <iostream>
#include <string>

#include "GameObject.hpp"

#include "Point2D.hpp"
#include "Trainer.hpp"
#include "View.hpp"

using namespace std;


class WildPokemon : public GameObject {
 public:
  WildPokemon(string in_name, double in_attack, double in_health, bool in_variant,
              int in_id, Point2D in_loc, char in_code = 'W');
  virtual ~WildPokemon();
  
  virtual void follow(Trainer*  t);    // Update WP's current_trainer & T's info

  bool   get_variant();
  double get_attack();
  double get_health();
  bool   get_in_combat();
  double get_track_dist();

  string get_name();
  bool   IsAlive();
  bool   ShouldBeVisible();

  bool   Update();
  void   ShowStatus();                                   // Overridden by Pidgey

 protected:
  double   attack    = 5;
  double   health    = 2;
  bool     variant   = false;
  bool     in_combat = false; // Return true if WildPokemon is following trainer
  string   name;
  Trainer* current_trainer = NULL;

  // Vars from Trainer to facilitate similar movement versatility
  Point2D  destination;
  Vector2D delta;
  double   track_dist;
  double   speed;

  bool     UpdateLocation();
  void     SetupDestination(Point2D dest);
};

enum WildPokemonStates {
  IN_ENVIRONMENT = 0,
  DEAD           = 1,
  IN_TRAINER     = 2
};

#endif
