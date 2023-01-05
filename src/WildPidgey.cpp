#include "../inc/WildPidgey.hpp"

extern const int view_maxsize;


// STRUCTORS....................................................................

WildPidgey::WildPidgey(string in_name, double in_attack, double in_health,
                       bool in_variant, int in_id, Point2D in_loc, char in_code)
          : WildPokemon(in_name, in_attack, in_health, in_variant, 
                        in_id, in_loc, in_code) {
  variant        = true;
  state          = IN_ENVIRONMENT;
  track_dist     = 4;                      // 4 seems like a reasonable value...
  speed          = 2;                      // 2 seems like a reasonable value...
  max_perch_time = 10;
  perch_time     = max_perch_time;
  perching       = false;
  cout << "WildPidgey constructed\n";
}

WildPidgey::~WildPidgey() {
  cout << "WildPidgey destructed,      ";
}


// UPDATE SEQ: follow -> SetupDestination -> Update -> 
//             UpdateLocation -> ShowStatus.....................................

void WildPidgey::follow(Trainer* t) { // Generic WP go to rand loc if no trainer
  current_trainer = t;
  if (current_trainer) {
    perching = false;
    perch_time = max_perch_time;
    if (GetDistanceBetween(location, current_trainer->GetLocation()) != 0.0) {
      SetupDestination(t->GetLocation());
    } else {
      state = IN_TRAINER;
      in_combat = true;
      current_trainer->change_num_attackers(1);
    }
  } else if (perching) {
    cout << "perching";
    if (GetDistanceBetween(location, current_building->GetLocation()) != 0.0) {
      SetupDestination(current_building->GetLocation());
    } else if (perch_time > 0) { 
      perch_time--; 
    } else {
      perching = false;
      perch_time = max_perch_time;
    }
  }
}

void WildPidgey::ShowStatus() {
  cout << name << " Status:";
  GameObject::ShowStatus();
  cout << "  Health:"         << setfill(' ') << setw(7) << health
       << "      Strength: "  << attack       << endl;
  if (current_trainer && IsAlive()) {
    cout << "  Stalking:  " << current_trainer->GetName() << "...\n";
  } else {
    cout << "  Stalking:  n/a\n";
  }
  if (get_in_combat() && IsAlive()) {
    cout << "  Attacking: " << current_trainer->GetName() << "!\n";
  } else {
    cout << "  Attacking: n/a\n";
  }
  if (perching && IsAlive()) {
    cout << "  Perch Loc: " << current_building->GetLocation() << endl;
  } else {
    cout << "  Perch Loc: n/a\n";
  }
}


// GETTERS AND SETTERS..........................................................

bool WildPidgey::get_perching() {
  return perching;
}

void WildPidgey::set_perching(bool if_perching) {
  perching = if_perching;
}

void WildPidgey::set_perch_num(int num_buildings) { 
  perch_num = num_buildings; 
}

void WildPidgey::set_perch(Building* b) {
  current_building = b;
}
