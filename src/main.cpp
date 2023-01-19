#include <iostream>
#include <string>

//#include "./inc/libfiglet.hpp"

#include "../inc/Model.hpp"
#include "../inc/View.hpp"
#include "../inc/GameCommand.hpp"
#include "../inc/Point2D.hpp"
#include "../inc/Vector2D.hpp"
#include "../inc/GameObject.hpp"
#include "../inc/Building.hpp"
#include "../inc/PokemonCenter.hpp"
#include "../inc/PokemonGym.hpp"
#include "../inc/Trainer.hpp"
#include "../inc/WildPokemon.hpp"
#include "../inc/Input_Handling.hpp"

#define ln cout << "(" << __LINE__ << ") ";                       // For testing

extern bool exiting;

using namespace std;

/* // Compiling requirements: c++11, 
g++ main.cpp Model.cpp View.cpp GameCommand.cpp Point2D.cpp Vector2D.cpp GameObject.cpp Building.cpp PokemonCenter.cpp PokemonGym.cpp Trainer.cpp WildPokemon.cpp WildPidgey.cpp
*/

/* TODO: To Do List
 - Final TODOs
 - Save states
 - Battle system
*/

int main() {

  // OPTIONS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  bool echo = false;                                          // echo user input

  // Figlet generator: For stability purposes, I pre-generate the message and 
  // paste it in. To compile w/ figlet, specify: -std=c++14
  // 
  //const srilakshmikanthanp::incfiglet::figlet 
  //  figlet(srilakshmikanthanp::libfiglet::flf_font::make_shared(
  //    "./Rectangles.flf"), 
  //    srilakshmikanthanp::libfiglet::smushed::make_shared()
  //  );
  //std::cout << figlet("Thanks for Playing!");

  cout << " _____     _                       __    _ _\n"
       << "|  _  |___| |_ ___ _____ ___ ___  |  |  |_| |_ ___\n"
       << "|   __| . | '_| -_|     | . |   | |  |__| |  _| -_|\n"
       << "|__|  |___|_,_|___|_|_|_|___|_|_| |_____|_|_| |___|\n\n";

  Model model = Model();
  View  view  = View();

  model.ShowStatus();
  model.Display(view);

  char op;   // m (move), c (move to Center), g (move to Gym), s (stop), 
             // p (buy potions), b (battles), a (advance), r (run), q (quit),
             // n (new object)
  int id1;   // m, c, d, s, p, b
  int id2;   // c, g
  double x;  // m
  double y;  // m
  int  p;    // p
  int  b;    // b
  char type; // n

  while (true) {

    cout << endl
         << "Move: m <T#> <x> <y>   To Gym: g <T#> <G#>    To Center: c <T#> <C#>\n"
         << "Stop: s                Battle: b <T#> <#>     Potions:   p <T#> <#>\n"
         << "Advance one tick: a    Run 5 or to event: r   Quit:      q\n"
         << "Create new game object: n <TYPE> <ID> <x> <y>\n"
         << "TYPEs: c(enter), g(ym), t(rainer), w(ildPokemon)\n";

    try {
      cout << "\nEnter a game command: ";
      if (!(cin >> op)) {
        cout << op;
        throw Invalid_Input("Cannot identify game command...");
      }

      switch (op) {                                // (Warning: op not init: OK)
        case 'm': { 
          if (echo) { cout <<"[input: move "<< id1 <<" to ("<< x << ", "<< y <<")]\n"; }
          if (!(cin >> id1)) {throw Invalid_Input("Move: Trainer input...");}
          if (!(cin >> x))   {throw Invalid_Input("Move: x input...");}
          if (!(cin >> y))   {throw Invalid_Input("Move: y input...");}
          DoMoveCommand(model, id1, Point2D(x, y));  break;
        }
        case 'c': {
          if (echo) { cout <<"[input: move "<< id1 <<" to pokemoncenter "<< id2 <<"]\n"; }
          if (!(cin >> id1)) {throw Invalid_Input("Center Move: Trainer input...");}
          if (!(cin >> id2)) {throw Invalid_Input("Center Move: Center input...");}
          DoMoveToCenterCommand(model, id1, id2);  break;
        }
        case 'g': {
          if (echo) { cout <<"[input: move "<< id1 <<" to pokemongym "<< id2 <<"]\n"; }
          if (!(cin >> id1)) {throw Invalid_Input("Gym Move: Trainer input...");}
          if (!(cin >> id2)) {throw Invalid_Input("Gym Move: Gym input...");}
          DoMoveToGymCommand(model, id1, id2);  break;
        }
        case 's': {
          if (echo) { cout << "[input: T" << id1 << " stop]\n"; }
          if (!(cin >> id1)) {throw Invalid_Input("Stop: Trainer input...");}
          DoStopCommand(model, id1);  break;
        }
        case 'p': {
          if (echo) { cout << "[input: T" << id1 << " buy " << p << " potions]\n"; }
          if (!(cin >> id1)) {throw Invalid_Input("Potion: Trainer input...");}
          if (!(cin >> p))   {throw Invalid_Input("Potion: Amount input...");}
          DoRecoverInCenterCommand(model, id1, p);  break;
        }
        case 'b': {
          if (echo) { cout << "[input: T" << id1 << " battle " << b << " battles]\n"; }
          if (!(cin >> id1)) {throw Invalid_Input("Battle: Trainer input...");}
          if (!(cin >> b))   {throw Invalid_Input("Battle: Amount input...");}
          DoBattleCommand(model, id1, b);  break;
        }
        case 'a': {
          if (echo) { cout << "[input: advance]\n"; }
          DoAdvanceCommand(model, view);  break;
        }
        case 'r': {
          if (echo) { cout << "[input: run]\n"; }
          DoRunCommand(model, view);  break;
        }
        case 'n' : {
          if (echo) { cout << "[input: new\n"; }
          if (!(cin >> type)) { throw Invalid_Input("New: Type input..."); }
          if (!(cin >> id1))  { throw Invalid_Input("New: ID input..."); }
          if (!(cin >> x))    { throw Invalid_Input("New: x input..."); }
          if (!(cin >> y))    { throw Invalid_Input("New: y input..."); }
          DoNewCommand(model, view, type, id1, Point2D(x, y)); break;
        }
        case 'q': {
          if (echo) { cout << "[input: quit]\n"; }
          cout << "You have quit the game!\n";
          // Exit from 'exiting' vars (not exit(0)) to ensure destructors called
          exiting = true;   break;
        }
        default: {
          throw Invalid_Input("Cannot parse game command...");
        }
      }

      if (exiting) {                                                     // Exit
        return 0;
      }
    }

    catch (Invalid_Input& except) {
      cout << "\n  Invalid input - " << except.msg_ptr << endl;
      continue;
    }
  }

  return 0;
}
