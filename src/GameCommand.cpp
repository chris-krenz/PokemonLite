#include "../inc/GameCommand.hpp" 


/* // GENERAL FLOW OF CONTROL
  main command 'g' -> this GameCommand.cpp DoMovingCommand() 
  -> Trainer.cpp StartMoving() sets state to MOVING
  -> back to main...
  Subsequent main command 'a' or 'r' 
  -> GameCommand.cpp DoAdvanceCommand() or DoRunCommand()
  -> Model.cpp Update() -> GameObject.cpp Update() poly to Trainer.cpp Update()
  -> this Trainer.cpp UpdateLocation() 
  (if arrived or fainted, return true to stop run loop)
  -> back to this GameCommand.cpp -> Model.cpp ShowStatus() -> Model.cpp Display()
  -> back to main...
*/


// MAIN COMMANDS: Move, MoveToCenter, MoveToGym, Stop, Battle, RecoverInCenter,
//                Advance, Run, New Object......................................

// Move Commands................................................................

void DoMoveCommand(Model& model, int trainer_id, Point2D p1) {
  Trainer* tPtr = model.GetTrainerPtr(trainer_id);
  if (tPtr) {
    cout << " Moving " << tPtr->GetName() << " to " << p1 << "...\n\n";
    tPtr->StartMoving(p1);
  } else {
    throw Invalid_Input("Move: Cannot identify trainer...");
  }
}

void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id) {
  Trainer*    tPtr = model.GetTrainerPtr(trainer_id);
  PokemonGym* gPtr = model.GetPokemonGymPtr(gym_id);
  if (tPtr) {
    if (gPtr) {
      cout << " Moving " << tPtr->GetName() << " to gym " << gPtr->GetID() <<"...\n\n";
      tPtr->StartMovingToGym(gPtr);
    } else {
      throw Invalid_Input("Gym Move: Cannot identify gym...");
    }
  } else {
    throw Invalid_Input("Gym Move: Cannot identify trainer...");
  }
}

void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id) {
  Trainer*       tPtr = model.GetTrainerPtr(trainer_id);
  PokemonCenter* cPtr = model.GetPokemonCenterPtr(center_id);
  if (tPtr) {
    if (cPtr) {
      cout << " Moving " << tPtr->GetName() << " to pokemon center "
           << cPtr->GetID() << "...\n\n";
      tPtr->StartMovingToCenter(cPtr);
    } else {
      throw Invalid_Input("Center Move: Cannot identify center...");
    }
  } else {
    throw Invalid_Input("Center Move: Cannot identify trainer...");
  }
}


// Building-Related Commands....................................................

void DoBattleCommand(Model& model, int trainer_id, unsigned int battles) {
  Trainer* tPtr = model.GetTrainerPtr(trainer_id);
  if (tPtr) {
    if (battles > 0) {
      cout << " " << tPtr->GetName() << " is battling...\n\n";
      tPtr->StartBattling(battles);
    } else {
      throw Invalid_Input("Battle: Battle number not valid...");
    }
  } else {
    throw Invalid_Input("Battle: Cannot identify trainer...");
  }
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, 
    unsigned int potions_needed) {
  Trainer* tPtr = model.GetTrainerPtr(trainer_id);
  if (tPtr) {
    if (potions_needed > 0) {
      cout << " Recovering " << tPtr->GetName() << "'s Pokemons' health...\n\n";
      tPtr->StartRecoveringHealth(potions_needed);
    } else {
      throw Invalid_Input("Potion: Potion number not valid...");
    }
  } else {
    throw Invalid_Input("Potion: Cannot identify trainer...");
  }
}


// Other Commands...............................................................

void DoStopCommand(Model& model, int trainer_id) {
  Trainer* tPtr = model.GetTrainerPtr(trainer_id);
  if (tPtr) {
    cout << " Stopping " << tPtr->GetName() << "...\n\n";
    tPtr->Stop();
  } else {
    throw Invalid_Input("Potion: Cannot identify trainer...");
  }
}

void DoAdvanceCommand(Model& model, View& view) {
  cout << " Advancing one tick...\n\n";
  model.Update();
  model.ShowStatus();
  model.Display(view);
}

void DoRunCommand(Model& model, View& view) {
  cout << " Advancing to next event...\n\n";
  for (int i = 0; i < 5; i++) {
    if (model.Update()) { break; }
  }
  model.ShowStatus();
  model.Display(view);
}

void DoNewCommand(Model& model, View& view, char Type, int id, Point2D p1) {
  cout << " Trying to create new object...\n\n";
  model.NewCommand(Type, id, p1);
}
