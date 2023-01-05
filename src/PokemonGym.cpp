#include "../inc/PokemonGym.hpp"


// STRUCTORS....................................................................

PokemonGym::PokemonGym(char in_code) : Building(in_code) {      // Default = 'G'
  max_number_of_battles      = 10;
  num_battle_remaining       = max_number_of_battles;
  health_cost_per_battle     = 1;
  PokeDollar_cost_per_battle = 1.0;
  experience_per_battle      = 2;
  state                      = NOT_DEFEATED;
  cout << "PokemonGym default constructed";
}

PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss,
                       double PokeDollar_cost, unsigned int exp_per_battle, 
                       int in_id, Point2D in_loc)
          : Building('G', in_id, in_loc) {
  max_number_of_battles      = max_battle;
  num_battle_remaining       = max_number_of_battles;
  health_cost_per_battle     = health_loss;
  PokeDollar_cost_per_battle = PokeDollar_cost;
  experience_per_battle      = exp_per_battle;
  state                      = NOT_DEFEATED;
  cout << "PokemonGym constructed";
}

PokemonGym::~PokemonGym() {
  cout << "PokemonGym destructed,      ";
}


// MEMBER FUNCTIONS.............................................................

// Called from Trainer...
unsigned int PokemonGym::TrainPokemon(unsigned int battle_units) {  
  if (num_battle_remaining > battle_units) {      // battle_units = num_battles
    num_battle_remaining -= battle_units;
    return battle_units * experience_per_battle;  // used by Update()
  } else {
    battle_units         = num_battle_remaining;
    num_battle_remaining = 0;
    return battle_units * experience_per_battle;  // used by Update()
  }
}

// Called from Model...
bool PokemonGym::Update() {
  if ((num_battle_remaining == 0) && (state == NOT_DEFEATED)) {
    state = DEFEATED;
    display_code = 'g';
    cout << display_code << id_num << " has been beaten.\n";
    return true;
  }
  return false;
}

// Called from Model...
void PokemonGym::ShowStatus() {
  cout << "Gym Status: ";
  Building::ShowStatus();
  cout << "   "
       << "  XP/battle: "        << setfill(' ') << setw(3) << experience_per_battle;
  cout << "\n  Max battles:"     << setfill(' ') << setw(3)
       << max_number_of_battles  << "   "
       << "  Remaining: "        << setfill(' ') << setw(3) << num_battle_remaining;
  cout << "\n  HP/battle:  "     << setfill(' ') << setw(3)
       << health_cost_per_battle << "   "
       << "  Cost/battle: "      << PokeDollar_cost_per_battle << endl;

}


// GETTERS AND STATUS CHECKERS..................................................

unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty) {
  return battle_qty * health_cost_per_battle;
}

double PokemonGym::GetPokeDollarCost(unsigned int battle_qty) {
  return battle_qty * PokeDollar_cost_per_battle;
}

unsigned int PokemonGym::GetExperiencePerBattle() {
  return experience_per_battle;
}

unsigned int PokemonGym::GetNumBattlesRemaining() {
  return num_battle_remaining;
}

bool PokemonGym::passed() {
  return num_battle_remaining == 0;
}

// Not currently using this function
bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget,
                                unsigned int health) {
  return (GetPokeDollarCost(battle_qty) <= budget
       && GetHealthCost(battle_qty) <  health);
}
