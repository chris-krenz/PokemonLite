#include "../inc/Trainer.hpp"


// STRUCTORS ...................................................................

Trainer::Trainer() : GameObject('T') {
  speed       = 5;
  state       = STOPPED;
  cout << "Trainer default constructed";
}

Trainer::Trainer(char in_code) : GameObject(in_code) {
  speed        = 5;
  state        = STOPPED;
  display_code = in_code;
  cout << "Trainer constructed";
}

Trainer::Trainer(string in_name, int in_id, char in_code, 
                 unsigned int in_speed, Point2D in_loc)
       : GameObject(in_code, in_id, in_loc) {
  speed        = in_speed;
  name         = in_name;
  display_code = in_code;
  id_num       = in_id;
  location     = in_loc;
  state        = STOPPED;
  cout << "Trainer " << name << " constructed";
}

Trainer::~Trainer() {
  cout << "Trainer destructed,         ";
}


// MAIN COMMAND FUNCTIONS: StartMoving, StartMovingToGym, StartMovingToCenter, 
//                         StartBattling, StartRecoveringHealth, Stop...........
// Vars/states updated here; actual changes (e.g. to hp or xp) occur in Update()

// Move Commands...

void Trainer::StartMoving(Point2D dest) {
  SetupDestination(dest);
  cout << " " << display_code << id_num << ": ";
  if (GetDistanceBetween(location, dest) == 0.0) {
    cout << " I'm already there. See?\n";
  } else if (HasFainted()) {
    cout << " My pokemon have fainted, so you cannot see me.\n";
  } else {
    if (is_IN_GYM)    {current_gym->RemoveOneTrainer();    is_IN_GYM    = false;}
    if (is_at_center) {current_center->RemoveOneTrainer(); is_at_center = false;}
    state = MOVING;
    cout << "On my way.\n";
  }
}

void Trainer::StartMovingToGym(PokemonGym* gym) {
  SetupDestination(gym->GetLocation());
  cout << display_code << id_num << ": ";
  if (GetDistanceBetween(location, destination) == 0.0) {
    cout << " I am already at the PokemonGym!\n";
  } else if (HasFainted()) {
    cout << " My pokemon have fainted so I can't move to gym.\n";
  } else {
    if (is_IN_GYM)    {current_gym->RemoveOneTrainer();    is_IN_GYM    = false;}
    if (is_at_center) {current_center->RemoveOneTrainer(); is_at_center = false;}
    current_gym = gym;
    state = MOVING_TO_GYM;
    cout << " On my way to gym " << gym->GetID() << ".\n";
  }
}

void Trainer::StartMovingToCenter(PokemonCenter* center) {    
  SetupDestination(center->GetLocation());
  cout << display_code << id_num << ": ";
  if (GetDistanceBetween(location, destination) == 0.0) {
    cout << " I am already at the Center!\n";
  } else if (HasFainted()) {
    cout << " My pokemon have fainted so I should have gone to the center....\n";
  } else {
    if (is_IN_GYM)    {current_gym->RemoveOneTrainer();    is_IN_GYM    = false;}
    if (is_at_center) {current_center->RemoveOneTrainer(); is_at_center = false;}
    current_center = center;
    state = MOVING_TO_CENTER;
    cout << " On my way to Center " << center->GetID() << ".\n";
  }
}

// Building-Related Commands...

void Trainer::StartBattling(unsigned int num_battles) {    
  cout << display_code << id_num << ": ";
  if (!is_IN_GYM) {
    cout << " I can only battle in a PokemonGym!\n";
  }
  else if (HasFainted()) {
    cout << " My pokemon have fainted so no more battles for me....\n";
  }
  else if (current_gym->GetPokeDollarCost(num_battles) > PokeDollars) {
    cout << " Not enough money for battles.\n";
  }
  else if (current_gym->GetNumBattlesRemaining() <= 0) {
    cout << " Cannot battle! This PokemonGym has no more trainers to battle!\n";
  }
  else {
    state = BATTLING_IN_GYM;
    cout << " Started to battle at the PokemonGym " << current_gym->GetID()
         << " with " << num_battles << " battles.\n";
    unsigned int hurt = current_gym->GetHealthCost(num_battles);
    if (hurt > health) {
      battles_to_buy = ceil(health/(hurt/num_battles));
      // (Warning: doub to unsign, data loss: OK; up to/including fatal battle)
      health = 0;
    } else {
      battles_to_buy = num_battles;
    }
  }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions) {
  cout << display_code << id_num << ": ";
  if (!is_at_center) {
    cout << " I can only recover health at a Pokemon Center!\n";
  }
  else if (!current_center->CanAffordPotion(num_potions, PokeDollars)) {
    cout << " Not enough money to recover health.\n";
  }
  else if (!current_center->HasPotions()) {
    cout << " Cannot recover! No potion remaining in this Pokemon Center.\n";
  }
  else {
    state = RECOVERING_HEALTH;
    cout << " Started recovering " << num_potions
         << " at Pokemon Center "  << current_center->GetID() << ".\n";
    potions_to_buy = current_center->DistributePotion(num_potions);
  }
}

// Other Command(s)...

void Trainer::Stop() {
  state = STOPPED;
  cout << " " << display_code << id_num << ": Stopping...\n";
}


// UPDATE SEQ: SetupDestination -> Update -> UpdateLocation -> ShowStatus.......

void Trainer::ShowStatus() {
  cout << name << " Status:";
  GameObject::ShowStatus();
  cout << "  Attackers:    " << num_attackers << "     Health:    " 
       << setfill(' ')       << setw(3)       << health   << endl;
  cout << "  PokeDollars:"   << setfill(' ')  << setw(6)  << PokeDollars
       << "  Experience:  "  << experience    << endl;

  switch (state) {
    case STOPPED: cout
      << "  Stopped" 
      << ".\n"; break;
    case MOVING: cout
      << "  Moving (speed: " << speed << ") to " << destination 
      << " (steps of: "      << delta << ")...\n"; break;
    case FAINTED: cout
      << "  FAINTED"
      << "!\n";  break;
    case AT_CENTER: cout
      << "  Inside Pokemon Center " << current_center->GetID()
      << ".\n"; break;
    case IN_GYM: cout
      << "  Inside PokemonGym " << current_gym->GetID()
      << ".\n"; break;
    case MOVING_TO_CENTER: cout
      << "  Heading to Center "   << current_center->GetID() << " (speed: " << speed 
      << ") (steps of: "          << delta                   << ")...\n"; break;
    case MOVING_TO_GYM: cout
      << "  Heading to Gym " << current_gym->GetID() << " (speed: " << speed
      << ") (steps of: "     << delta                << ")...\n"; break;
    case BATTLING_IN_GYM: cout
      << "  Battling in PokemonGym " << current_gym->GetID()
      << "!\n"; break;
    case RECOVERING_HEALTH: cout
      << "  Recovering health in Pokemon Center " << current_center->GetID()
      << "...\n"; break;
    default: break;
  }
}

// States: STOPPED, MOVING, FAINTED, AT_CENTER, IN_GYM, MOVING_TO_CENTER, 
//         MOVING_TO_GYM, BATTLING_IN_GYM, RECOVERING_HEALTH
bool Trainer::Update() {                                       // TODO: Simplify
  switch (state) {
    case STOPPED: return false;
    case MOVING: {
      if (UpdateLocation()) { 
        state = STOPPED; 
        return true;
      } else if (HasFainted()) {
        state = FAINTED; 
        cout << name << " is out of health and can't move.\n";
        return true;
      } else {
        return false;
      }
    }
    case FAINTED:   return false;
    case AT_CENTER: is_at_center = true; return false;  //is_at_center redundant
    case IN_GYM:    is_IN_GYM    = true; return false;  //is_IN_GYM redundant
    case MOVING_TO_CENTER:  {
      if (UpdateLocation()) {
        state = AT_CENTER; 
        is_at_center = true; 
        current_center->AddOneTrainer();
        return true;
      } else if (HasFainted()) {
        state = FAINTED; 
        cout << name << " is out of health and can't move.\n";
        return true;
      } else {
        return false;
      }
    }
    case MOVING_TO_GYM:  {          // Should only enter if *not* already in Gym
      if (UpdateLocation()) {
        state = IN_GYM;                     // Will all update *even* if fainted
        is_IN_GYM = true;
        current_gym->AddOneTrainer();
      } 
      if (HasFainted()) {
        state = FAINTED;
        cout << name << " is out of health and can't move.\n";
      }
      return (state == IN_GYM || state == FAINTED);
    }
    case BATTLING_IN_GYM:  {
      PokeDollars -= current_gym->GetPokeDollarCost(battles_to_buy);
      unsigned int exp = current_gym->TrainPokemon(battles_to_buy);
      experience += exp;
      cout << "** " << name << " completed " << battles_to_buy << " battles! **\n";
      cout << "** " << name << " gained "    << exp            << " experience! **\n";
      if (HasFainted()) {
        state = FAINTED;
        cout << "** But unfortunately, " << name << " has fainted! :-( **\n";
        return true;
      } else {
        health -= current_gym->GetHealthCost(battles_to_buy);
        state = IN_GYM;
        return true;
      }
    }
    case RECOVERING_HEALTH:  {
      int heal = potions_to_buy*5;
      health += heal;
      if (health > 100) { health = 100; }
      PokeDollars -= current_center->GetPokeDollarCost(potions_to_buy);
      cout << "** " << name << " recovered " << heal           << " health! **\n";
      cout << "** " << name << " bought "    << potions_to_buy << " potions! **\n";
      state = AT_CENTER;
      return true; 
    }
    default: cout << "STATE ERROR\n";  return false;
  }
}

void Trainer::SetupDestination(Point2D dest) {
  destination = dest;
  delta = (dest - location)*(speed/GetDistanceBetween(dest, location));
}

bool Trainer::UpdateLocation() {
  location = location + delta;
  if (health > 0)  { health -= 1; }
  if (health > 0)  { PokeDollars += GetRandomAmountOfPokeDollars(); }
  if ((fabs(destination.x - location.x) <= fabs(delta.x))
   && (fabs(destination.y - location.y) <= fabs(delta.y))) {
    location = destination;
    cout << " ...arrived\n";
    return true;
  } else {
    cout << " ...moved\n";
    return false;
  }
}


// GETTERS......................................................................

string Trainer::GetName() { return name; }

bool Trainer::HasFainted() {
  if (health == 0) { return true; }
  else { return false; }
}

bool Trainer::ShouldBeVisible() {
  if (!HasFainted()) { return true; }
  else { return false; }
}


// SETTERS......................................................................

bool Trainer::decrement_health(unsigned int damage) {
  if (damage >= health) {
    health = 0;
    state = FAINTED;
    return true;
  } else {
    health -= damage;
    return false;
  }
}

void Trainer::change_num_attackers(int signed_change) {
  if (signed_change == 0) {
    num_attackers = 0;
  } else {
    num_attackers += signed_change;
  }
}


//NON-MEMBER FUNCS..............................................................

static double GetRandomAmountOfPokeDollars() {
  srand(time(NULL));   // (Warning: arg convert time_t to unsign, data loss: OK)
  rand();                  // (Warning: val ignored: OK; improves randomization)
  double rand1 = (double)rand() / ((double)RAND_MAX / 2.0);
  return rand1;
}
