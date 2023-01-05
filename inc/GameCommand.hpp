#ifndef GAMECOMMAND_HPP_
#define GAMECOMMAND_HPP_

#include <iostream>
#include <string>

#include "Model.hpp"
#include "Point2D.hpp"
#include "View.hpp"
#include "Input_Handling.hpp"

using namespace std;

void DoMoveCommand            (Model& model, int trainer_id, Point2D p1);
void DoMoveToGymCommand       (Model& model, int trainer_id, int gym_id);
void DoMoveToCenterCommand    (Model& model, int trainer_id, int center_id);
void DoBattleCommand          (Model& model, int trainer_id, unsigned int battles);
void DoRecoverInCenterCommand (Model& model, int trainer_id, unsigned int potions_needed);
void DoStopCommand            (Model& model, int trainer_id);
void DoAdvanceCommand         (Model& model, View& view);
void DoRunCommand             (Model& model, View& view);
void DoNewCommand             (Model& model, View& view, char Type, int id, Point2D p1);

#endif
