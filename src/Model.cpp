#include "../inc/Model.hpp"

#define ln cout << "(" << __LINE__ << ") ";                       // For testing

bool exiting = false;


//STRUCTORS.....................................................................

// Contains pointers representing all game objects & w/ which Updates are called
Model::Model() {
  time            = 0;

  // DEFAULT TRAINERS      // name, id, code, speed, loc
   Trainer* pT1 = new Trainer("Ash", 1, 'T', 1, Point2D(5, 1));
    object_ptrs.push_back(pT1);
    active_ptrs.push_back(pT1);
    trainer_ptrs.push_back(pT1);
   Trainer* pT2 = new Trainer("Misty", 2, 'T', 2, Point2D(10, 1));
    object_ptrs.push_back(pT2);
    active_ptrs.push_back(pT2);
    trainer_ptrs.push_back(pT2);

  // DEFAULT CENTERS                  // id, $, cap, loc
   PokemonCenter* pC1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    object_ptrs.push_back(pC1);
    active_ptrs.push_back(pC1);
    building_ptrs.push_back(pC1);
    center_ptrs.push_back(pC1);
   PokemonCenter* pC2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
    object_ptrs.push_back(pC2);
    active_ptrs.push_back(pC2);
    building_ptrs.push_back(pC2);
    center_ptrs.push_back(pC2);

  // DEFAULT GYMS           // battles,hp, $,xp,id, loc
   PokemonGym* pG1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0, 0));
    object_ptrs.push_back(pG1);
    active_ptrs.push_back(pG1);
    building_ptrs.push_back(pG1);
    gym_ptrs.push_back(pG1);
   PokemonGym* pG2 = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5, 5));
    object_ptrs.push_back(pG2);
    active_ptrs.push_back(pG2);
    building_ptrs.push_back(pG2);
    gym_ptrs.push_back(pG2);

  // WILDPOKEMON                    // name, attack, health, variant, id, in_loc
   WildPokemon* pW1 = new WildPokemon("Rattata-the-Rounder", 1.0, 6.0, false, 1, 
                                      Point2D(15, 5));
    object_ptrs.push_back(pW1);
    active_ptrs.push_back(pW1);
    wildpokemon_ptrs.push_back(pW1);


// OPTIONAL POKEMON VARIANTS...
  // WILDPIDGEY                     // name, attack, health, variant, id, in_loc
    WildPidgey* pP2 = new WildPidgey("Pidgey-the-Percher", 1.0, 3.0, true, 2,
                                      Point2D(10, 12));
      object_ptrs.push_back(pP2);
      active_ptrs.push_back(pP2);
      wildpokemon_ptrs.push_back(pP2);

  cout << "Model default constructed\n";
}

Model::~Model() {
  for (list <GameObject*>::iterator GameObjectIter = object_ptrs.begin();
       GameObjectIter != object_ptrs.end();
       ++GameObjectIter) {
    (*GameObjectIter)->~GameObject();
    //*GameObjectIter = NULL;
    //delete *GameObjectIter;
  }
cout << "Model destructed\n\n"
<< "******************************** Credits *********************************\n\n"
<< "Programming/Debugging:  Chris Krenz (github: chris-krenz)\n"
<< "Basic Concept/Specs:    BU EC327 Faculty\n"
<< "Figlet Library:         Sri Lakshmi Kanthan P (github: srilakshmikanthanp)\n\n";
cout
<<"                                                                     __\n"
<<" _____ _           _         ___           _____ _         _        |  |\n"
<<"|_   _| |_ ___ ___| |_ ___  |  _|___ ___  |  _  | |___ _ _|_|___ ___|  |\n"
<<"  | | |   | .'|   | '_|_ -| |  _| . |  _| |   __| | .'| | | |   | . |__|\n"
<<"  |_| |_|_|__,|_|_|_,_|___| |_| |___|_|   |__|  |_|__,|_  |_|_|_|_  |__|\n"
<<"                                                      |___|     |___|\n";
cin.clear();
cin.ignore(1000, '\n');
cout << "(Any entry to exit)";
getchar();
}


// NEW OBJECT FUNCTION..........................................................

void Model::NewCommand(char Type, int id, Point2D p1) {
  switch (Type) {
    case 'c': {
      if ((id > 0) && (id < 10) && !GetPokemonCenterPtr(id)) {
        PokemonCenter* newCenter = new PokemonCenter(
          id/*id*/, 1/*$*/, 100/*cap*/, p1/*loc*/
        );
        object_ptrs.push_back(newCenter);
        active_ptrs.push_back(newCenter);
        building_ptrs.push_back(newCenter);
        center_ptrs.push_back(newCenter);
      } else {
        cout << "Sorry, that ID is taken.";
      } break;
    }
    case 'g': {
      if ((id > 0) && (id < 10) && !GetPokemonGymPtr(id)) {
        PokemonGym* newGym = new PokemonGym(
          10/*battles*/, 1/*hp*/, 2/*$*/, 3/*xp*/, id/*id*/, p1/*loc*/
        );
        object_ptrs.push_back(newGym);
        active_ptrs.push_back(newGym);
        building_ptrs.push_back(newGym);
        gym_ptrs.push_back(newGym);
      } else {
        cout << "Sorry, that ID is taken.";
      } break;
    }
    case 't': {
      if ((id > 0) && (id < 10) && !GetTrainerPtr(id)) {
        Trainer* newTrainer = new Trainer(
          "Brock"/*name*/, id/*id*/, 'T'/*code*/, 1/*speed*/, p1/*loc*/
        );
        object_ptrs.push_back(newTrainer);
        active_ptrs.push_back(newTrainer);
        trainer_ptrs.push_back(newTrainer);
      } else {
        cout << "Sorry, that ID is taken.";
      } break;
    }
    case 'w': {
      if ((id > 0) && (id < 10) && !GetWildPokemonPtr(id)) {
        WildPokemon* newPokemon = new WildPokemon(
          "JigglyPuff"/*name*/, 1.0/*attack*/, 3.0/*health*/, false/*variant*/, 
          id/*id*/, p1/*in_loc*/
        );
        object_ptrs.push_back(newPokemon);
        active_ptrs.push_back(newPokemon);
        wildpokemon_ptrs.push_back(newPokemon);
      } else {
        cout << "Sorry, that ID is taken.";
      } break;
    }
  }
}


// FUNC SEQ (from GameCommand): Update -> ShowStatus -> Display.................

bool Model::Update() {
  time++;

  bool update_occurred = false;            // WP move is not a meaningful update
  list <GameObject*>::iterator ActiveObjectIter;
  for (ActiveObjectIter = active_ptrs.begin();
       ActiveObjectIter != active_ptrs.end();
       ++ActiveObjectIter) {
    //ln cout << "Update test\n";
    if ((*ActiveObjectIter)->Update()) {
      update_occurred = true;
    }
  }

  list <Trainer*>::iterator TrainerIter;
  for (TrainerIter = trainer_ptrs.begin();
       TrainerIter != trainer_ptrs.end(); 
       ++TrainerIter) {
    //ln cout << "Num attackers test\n";
    (*TrainerIter)->change_num_attackers(0);      // Reset T attackers each time
  }

  list <WildPokemon*>::iterator WildPokemonIter;
  for (WildPokemonIter = wildpokemon_ptrs.begin();   // 1: For each WP...
       WildPokemonIter != wildpokemon_ptrs.end(); 
       ++WildPokemonIter) {
    //ln cout << "WP model update test\n";
    int     following = false;
    int     followed_trainer;
    Point2D wp_loc     = (*WildPokemonIter)->GetLocation();
    double  track_dist = (*WildPokemonIter)->get_track_dist();

    for (TrainerIter = trainer_ptrs.begin();         // 2: And for each T...
         TrainerIter != trainer_ptrs.end();
         ++TrainerIter) {
      Point2D t_loc = (*TrainerIter)->GetLocation();
      double  dist  = GetDistanceBetween(wp_loc, t_loc);
      
      if (dist < track_dist) {                       // 3: If T closest in range
        track_dist = dist;
        followed_trainer = distance(trainer_ptrs.begin(), TrainerIter);
        following = true;
      }
    }

    if (following) {                                 // 4: Then WP follows T
      //ln cout << "WP -> following model update test\n";
      (*WildPokemonIter)->follow(*next(trainer_ptrs.begin(), followed_trainer));
    } else {                                         // 5: Else other movement
      // \/ gets/sets variant-specific info; returns NULL if not derived type...
      if (WildPidgey* pidgey = dynamic_cast<WildPidgey*>(*WildPokemonIter)) {
        if (pidgey->get_perching() == false) {
          srand(std::time(NULL) + pidgey->GetID() + 
                pidgey->GetLocation().x*pidgey->GetLocation().y);
          rand();          // (Warning: val ignored: OK; improves randomization)
          int rand_build = rand() / (RAND_MAX / building_ptrs.size());
          pidgey->set_perch(*next(building_ptrs.begin(), rand_build));
          pidgey->set_perching(true);
        }
      }
      (*WildPokemonIter)->follow(NULL);
    }
  }

  int num_fainted = 0;
  for (TrainerIter = trainer_ptrs.begin();
       TrainerIter != trainer_ptrs.end();
       ++TrainerIter) {
    //ln cout << "Trainer faint update test\n";
    if ((*TrainerIter)->GetState() == FAINTED) {
      num_fainted++;
    }
  }
  if (num_fainted >= trainer_ptrs.size()) {
    cout << "Game Over: You LOSE! All of your Trainers' Pokemon have fainted!\n";
    cout << "Final State...\n";
    exiting = true;
  }

  list <PokemonGym*>::iterator PokemonGymIter;
  int num_defeated = 0;
  for (PokemonGymIter = gym_ptrs.begin();
       PokemonGymIter != gym_ptrs.end();
       ++PokemonGymIter) {
    if ((*PokemonGymIter)->GetState() == DEFEATED) {
      num_defeated++;
    }
  }
  if (num_defeated >= gym_ptrs.size()) {
    cout << "Game Over: You WIN! All battles done!\n";
    cout << "Final State...\n";
    exiting = true;
  }

  ActiveObjectIter = active_ptrs.begin();  // If erasing element, use while loop
  while (ActiveObjectIter != active_ptrs.end()) {
    if (!((*ActiveObjectIter)->ShouldBeVisible())) {
      ActiveObjectIter = active_ptrs.erase(ActiveObjectIter);
      cout << "Dead object (" << distance(active_ptrs.begin(), ActiveObjectIter) 
           << ") removed.\n";
    } else {
      ActiveObjectIter++;
    }
  }

  return update_occurred;
}

void Model::ShowStatus() {
  cout << endl;
  //ln cout << "Show Status test\n";
  for (list <GameObject*>::iterator GameObjectIter = object_ptrs.begin();
       GameObjectIter != object_ptrs.end();
       ++GameObjectIter) {
    (*GameObjectIter)->ShowStatus();
    cout << endl;
  }
}

void Model::Display(View& view) {
  cout << "       TIME: " << time << endl;
  view.Clear();
  //ln cout << "Display test\n";
  for (list <GameObject*>::iterator GameObjectIter = object_ptrs.begin();
       GameObjectIter != object_ptrs.end();
       ++GameObjectIter) {
    view.Plot(*GameObjectIter);
  }
  view.Draw();
}


// GETTERS......................................................................

int Model::get_num_buildings() { return building_ptrs.size(); }

Trainer* Model::GetTrainerPtr(int id) {
  for (list <Trainer*>::iterator TrainerIter = trainer_ptrs.begin();
       TrainerIter != trainer_ptrs.end();
       ++TrainerIter) {
    if ((*TrainerIter)->GetID() == id) {
      return *TrainerIter;
    }
  }
  return 0;
}

Building* Model::GetBuildingPtr(int id) {
  for (list <Building*>::iterator BuildingIter = building_ptrs.begin();
       BuildingIter != building_ptrs.end();
       ++BuildingIter) {
    if ((*BuildingIter)->GetID() == id) {
      return *BuildingIter;
    }
  }
  return 0;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id) {
  for (list <PokemonCenter*>::iterator PokemonCenterIter = center_ptrs.begin();
       PokemonCenterIter != center_ptrs.end();
       ++PokemonCenterIter) {
    if ((*PokemonCenterIter)->GetID() == id) {
      return *PokemonCenterIter;
    }
  }
  return 0;
}

PokemonGym* Model::GetPokemonGymPtr(int id) {
  for (list <PokemonGym*>::iterator PokemonGymIter = gym_ptrs.begin();
       PokemonGymIter != gym_ptrs.end();
       ++PokemonGymIter) {
    if ((*PokemonGymIter)->GetID() == id) {
      return *PokemonGymIter;
    }
  }
  return 0;
}

WildPokemon* Model::GetWildPokemonPtr(int id) {
  for (list <WildPokemon*>::iterator WildPokemonIter = wildpokemon_ptrs.begin();
       WildPokemonIter != wildpokemon_ptrs.end();
       ++WildPokemonIter) {
    if ((*WildPokemonIter)->GetID() == id) {
      return *WildPokemonIter;
    }
  }
  return 0;
}
