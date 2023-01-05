#include "../inc/WildPokemon.hpp"

extern const int view_maxsize;


// STRUCTORS....................................................................

WildPokemon::WildPokemon(string in_name, double in_attack, double in_health,
                         bool in_variant, int in_id, Point2D in_loc, char in_code)
           : GameObject(in_code, in_id, in_loc) {
  name       = in_name;
  attack     = in_attack;
  health     = in_health;
  variant    = in_variant;
  state      = IN_ENVIRONMENT;
  track_dist = 4;                          // 4 seems like a reasonable value...
  speed      = 2;                          // 2 seems like a reasonable value...
  cout << "WildPokmeon default constructed,   ";
}

WildPokemon::~WildPokemon() {
  cout << "WildPokemon destructed,     ";
}


// UPDATE SEQ: follow -> SetupDestination -> Update -> 
//             UpdateLocation -> ShowStatus.....................................

void WildPokemon::follow(Trainer* t) { // Generic WP go to rand loc if no trainer
  current_trainer = t;
  if (current_trainer) {
    if (GetDistanceBetween(location, current_trainer->GetLocation()) != 0.0) {
      SetupDestination(t->GetLocation());
    } else {
      state     = IN_TRAINER;
      in_combat = true;
      current_trainer->change_num_attackers(1);
    }
  } else {                    // This randomization ensures each WP is different
    srand(time(NULL) + GetID() + GetLocation().x*GetLocation().y);
    // (Warning: arg convert time_t to unsign, data loss: OK)
    rand();                // (Warning: val ignored: OK; improves randomization)
    double rand_x = (double)rand() / ((double)RAND_MAX / (view_maxsize));
    double rand_y = (double)rand() / ((double)RAND_MAX / (view_maxsize));
    Point2D rand_dest = Point2D(rand_x, rand_y);
    SetupDestination(rand_dest);
  }
}

void WildPokemon::SetupDestination(Point2D dest) {
  destination = dest;
  delta = (dest - location)*(speed/GetDistanceBetween(dest, location));
}

bool WildPokemon::Update() {
  switch (state) {
    case DEAD: {
      return false;
    }
    case IN_TRAINER: {
      if (!IsAlive()) {
        state = DEAD;
        in_combat = false;
        current_trainer = NULL;
        cout << name << " has died...\n";
        return true;
      }
      current_trainer->decrement_health(attack);      // WP and T health updated
      health--;
      cout << name << " attacked " << current_trainer->GetName() << "!\n";
      if (GetDistanceBetween(location, current_trainer->GetLocation()) == 0.0) {
        return false;
      } else {
        state = IN_ENVIRONMENT;
        in_combat = false;
        cout << name << " stopped attacking " << current_trainer->GetName() << "!\n";
        return true;
      }
    }
    case IN_ENVIRONMENT: {
      if (!IsAlive()) {
        state = DEAD;
        in_combat = false;
        current_trainer = NULL;
        cout << name << " has died...\n";
        return true;
      }
      bool arrived = UpdateLocation();
      if (arrived && (current_trainer != NULL)) {
        state = IN_TRAINER;
        in_combat = true;
        cout << name << " started attacking " << current_trainer->GetName() << "!\n";
        return true;
      } else {
        return false;
      }
    }
    default: return false;
  }
}

bool WildPokemon::UpdateLocation() {
  if ((fabs(destination.x - location.x) <= fabs(delta.x))
   && (fabs(destination.y - location.y) <= fabs(delta.y))) {
    location = destination;
    return true;
  } else {
    location = location + delta;
    return false;
  }
}

void WildPokemon::ShowStatus() {
  cout << name << " Status:";
  GameObject::ShowStatus();
  cout << "  Health:"         << setfill(' ') << setw(7) << health 
       << "      Strength: "  << attack       << endl;
  if (current_trainer && IsAlive()) {
    cout << "  Stalking:  " << current_trainer->GetName() << "...\n";
    cout << current_trainer;
  } else {
    cout << "  Stalking:  n/a\n";
  }
  if (get_in_combat() && IsAlive()) {
    cout << "  Attacking: " << current_trainer->GetName() << "!\n";
  } else {
    cout << "  Attacking: n/a\n";
  }
}


// STATUS CHECKERS..............................................................

bool WildPokemon::IsAlive() {
  if (health == 0) { return false; }
  else { return true; }
}

bool WildPokemon::ShouldBeVisible() {
  if (!IsAlive()) { return false; }
  else { return true; }
}


// GETTERS......................................................................

bool   WildPokemon::get_variant()    { return variant;    }

double WildPokemon::get_attack()     { return attack;     }

double WildPokemon::get_health()     { return health;     }

bool   WildPokemon::get_in_combat()  { return in_combat;  }

double WildPokemon::get_track_dist() { return track_dist; }

string WildPokemon::get_name()       { return name;       }
