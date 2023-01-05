#ifndef TRAINER_HPP_
#define TRAINER_HPP_

// ~Google preferred inclusion order...
#include <time.h>
#include <math.h>

#include <iostream>
#include <string>

#include "GameObject.hpp"

#include "Point2D.hpp"
#include "Vector2D.hpp"
#include "PokemonCenter.hpp"
#include "PokemonGym.hpp"

using namespace std;


class Trainer : public GameObject {
 public:
  Trainer();
  Trainer(char in_code);
  Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, 
          Point2D in_loc);
  virtual ~Trainer();

  void   StartMoving(Point2D dest);
  void   StartMovingToGym(PokemonGym* gym);
  void   StartMovingToCenter(PokemonCenter* center);
  void   StartBattling(unsigned int num_battles);
  void   StartRecoveringHealth(unsigned int num_potions);
  void   Stop();

  string GetName();
  bool   HasFainted();
  bool   ShouldBeVisible();
  bool   decrement_health(unsigned int damage);
  void   change_num_attackers(int signed_change);

  bool   Update();
  void   ShowStatus();

 protected:
  bool UpdateLocation();
  void SetupDestination(Point2D dest);

 private:
  double      speed                 = 0.0;
  unsigned int health               = 20;
  //unsigned int   health         = 100;  // For testing
  double      PokeDollars           = 0;
  //double         PokeDollars    = 500;  // For testing
  unsigned int experience           = 0;
  unsigned int battles_to_buy       = 0;
  unsigned int potions_to_buy       = 0;
  string      name;

  int            num_attackers  = 0;
  bool           is_IN_GYM      = false;
  bool           is_at_center   = false;
  PokemonGym*    current_gym    = NULL;
  PokemonCenter* current_center = NULL;

  Point2D        destination;                           // initialized to origin
  Vector2D       delta;
};

static double GetRandomAmountOfPokeDollars();

enum TrainerStates {
  STOPPED           = 0,
  MOVING            = 1,
  FAINTED           = 2,
  AT_CENTER         = 3,
  IN_GYM            = 4,
  MOVING_TO_CENTER  = 5,
  MOVING_TO_GYM     = 6,
  BATTLING_IN_GYM   = 7,
  RECOVERING_HEALTH = 8
};

#endif
