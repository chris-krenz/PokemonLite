#include "../inc/PokemonCenter.hpp"


// STRUCTORS....................................................................

PokemonCenter::PokemonCenter(char in_code) : Building(in_code) { //Default = 'C'
  pokedollar_cost_per_potion = 5;
  potion_capacity            = 100;
  num_potions_remaining      = potion_capacity;
  state                      = POTIONS_AVAILABLE;
  cout << "PokemonCenter default constructed";
}

PokemonCenter::PokemonCenter(int in_id, double potion_cost, 
                             unsigned int potion_cap, Point2D in_loc) 
             : Building('C', in_id, in_loc) {
  pokedollar_cost_per_potion = potion_cost;
  potion_capacity            = potion_cap;
  num_potions_remaining      = potion_capacity;
  state                      = POTIONS_AVAILABLE;
  cout << "PokemonCenter constructed";
}

PokemonCenter::~PokemonCenter() {
  cout << "PokemonCenter destructed,   ";
}


// MEMBER FUNCTIONS.............................................................

// Called from Trainer...
unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed) {
  if (num_potions_remaining > potion_needed) {
    num_potions_remaining -= potion_needed;
    return potion_needed;
  } else {
    potion_needed = num_potions_remaining;
    num_potions_remaining = 0;
    return potion_needed;
  }
}

// Called from Model...
bool PokemonCenter::Update() {
  if (num_potions_remaining == 0 && state == POTIONS_AVAILABLE) {
    state = NO_POTIONS_AVAILABLE;
    display_code = 'c';
    cout << "PokemonCenter " << id_num << " has run out of potions.\n";
    return true;
  }
  return false;
}

// Called from Model...
void PokemonCenter::ShowStatus() {
  cout << "Center Status: ";
  Building::ShowStatus();
  cout << "     Potion Cost: "  << pokedollar_cost_per_potion << endl
       << "  Stock:      "      << setfill(' ') << setw(3) 
       << num_potions_remaining << endl;
}


// GETTERS AND STATUS CHECKERS..................................................

bool PokemonCenter::HasPotions() {
  return num_potions_remaining > 0;
}

unsigned int PokemonCenter::GetNumPotionRemaining() {
  return num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget) {
  return budget >= GetPokeDollarCost(potion);
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion) {
  return pokedollar_cost_per_potion * potion;
}
