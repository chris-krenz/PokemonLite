#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <time.h>
#include <math.h>

#include <iostream>
#include <list>
#include <string>
#include <sstream>

#include "Point2D.hpp"
#include "Vector2D.hpp"
#include "GameObject.hpp"
#include "PokemonCenter.hpp"
#include "PokemonGym.hpp"
#include "Trainer.hpp"
#include "WildPokemon.hpp"
#include "WildPidgey.hpp"
#include "View.hpp"

using namespace std;  // Google style strongly discourages 'using' directives...


class Model {
 public:
  Model();
  virtual ~Model();

  Trainer*       GetTrainerPtr       (int id);
  Building*      GetBuildingPtr      (int id);
  PokemonCenter* GetPokemonCenterPtr (int id);
  PokemonGym*    GetPokemonGymPtr    (int id);
  WildPokemon*   GetWildPokemonPtr   (int id);

  bool Update();
  void Display(View& view);
  void ShowStatus();
  void NewCommand(char Type, int id, Point2D p1);

 private:
  int time;

  int get_num_buildings();

  list <GameObject*>    object_ptrs;
  list <GameObject*>    active_ptrs;
  list <Trainer*>       trainer_ptrs;
  list <Building*>      building_ptrs;
  list <PokemonCenter*> center_ptrs;
  list <PokemonGym*>    gym_ptrs;
  list <WildPokemon*>   wildpokemon_ptrs;
};

#endif
