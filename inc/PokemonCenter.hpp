#ifndef POKEMONCENTER_HPP_
#define POKEMONCENTER_HPP_

#include <iostream>

#include "GameObject.hpp"
#include "Building.hpp"

using namespace std;


class PokemonCenter : public Building {
 public:
  PokemonCenter(char in_code = 'C');
  PokemonCenter(int in_id, double potion_cost,
                unsigned int potion_cap, Point2D in_loc);
  virtual ~PokemonCenter();

  bool         HasPotions           ();
  unsigned int GetNumPotionRemaining();
  bool         CanAffordPotion      (unsigned int potion, double  budget);
  double       GetPokeDollarCost    (unsigned int potion);
  unsigned int DistributePotion     (unsigned int potion_needed);

  bool         Update               ();
  void         ShowStatus           ();

 private:
  unsigned int potion_capacity;
  unsigned int num_potions_remaining;
  double       pokedollar_cost_per_potion;
};

enum PokemonCenterStates {
  POTIONS_AVAILABLE    = 0,
  NO_POTIONS_AVAILABLE = 1
};

#endif
