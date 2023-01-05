#ifndef POKEMONGYM_HPP_
#define POKEMONGYM_HPP_

#include <iostream>

#include "GameObject.hpp"
#include "Building.hpp"

using namespace std;


class PokemonGym : public Building {
 public:
  PokemonGym(char in_code = 'G');
  PokemonGym(unsigned int max_battle, unsigned int health_loss,
             double PokeDollar_cost, unsigned int exp_per_battle,
             int in_id, Point2D in_loc);
  virtual ~PokemonGym();

  unsigned int GetHealthCost         (unsigned int battle_qty);
  double       GetPokeDollarCost     (unsigned int battle_qty);
  unsigned int GetNumBattlesRemaining();
  bool         passed();                                     // Currently unused
  unsigned int GetExperiencePerBattle();
  unsigned int TrainPokemon          (unsigned int battle_units);
  bool         IsAbleToBattle        (unsigned int battle_qty, double budget,
                                      unsigned int health);  // Currently unused

  bool         Update                ();
  void         ShowStatus            ();

 private:
  unsigned int num_battle_remaining;
  unsigned int max_number_of_battles;
  unsigned int health_cost_per_battle;
  unsigned int experience_per_battle;
  double       PokeDollar_cost_per_battle;
};

enum PokemonGymStates {
  NOT_DEFEATED = 0,
  DEFEATED     = 1
};

#endif
