#include "../inc/Building.hpp"


// STRUCTORS....................................................................

Building::Building(char in_code) : GameObject(in_code) {        // Default = 'B'
  trainer_count = 0;
  cout << "Building default constructed,              ";
}

Building::Building(char in_code, int in_Id, Point2D in_loc) 
        : GameObject(in_code, in_Id, in_loc) {
  trainer_count = 0;
  cout << "Building constructed,              ";
}

Building::~Building() {
  cout << "Building destructed,        ";
}


// FUNCTIONS....................................................................

// Print PokemonCenter or PokemonGym status; generally call after Model.Update()
void Building::ShowStatus() {
  cout << display_code << id_num << " at " << location << ": \n" 
       << "  Trainers:     " << trainer_count;
}

bool Building::ShouldBeVisible() {                           // Currently unused
  return true;
}


// SETTERS......................................................................

void Building::AddOneTrainer()    { trainer_count++; }

void Building::RemoveOneTrainer() { trainer_count--; }
