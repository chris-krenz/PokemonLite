POKEMON LITE: A simple C++ console game


Compilation:
 - Use `make PokeLite' to compile
 - Recommend c++11


Documentation:
 - ClassDiagram.cd
 - Flow-Chart.drawio
 - Control flow explanation at the beginning of GameCommand.cpp
 - Uses a Model-View-Controller paradigm
 - Styled according to the Google C++ Style Guide


Available player actions:
 - Move trainers around a ~20x20 grid (losing health but earning PokeDollars)
 - Encounter Wild Pokemon (draining health of both trainer and pokemon)
 - Recover health at Pokemon Centers
 - Fight battles at Pokemon Gyms
 - Advance time 1 or 5 steps at a time
 - Create new buildings, trainers, or pokemon
 - Win by defeating all gyms
 - Lose if all Trainers faint


WildPokemon strats:
 - All WildPokemon stalk Trainers if within a certain range
 - General default WildPokemon go to a random location if no Trainer is nearby
 - Pidgey class WildPokemon head to a random building and wait awhile; 
   if no trainer comes, they go to another random building.


Credits:
 - Programming/Debugging by Chris Krenz (github: chris-krenz)
    - For the EC327 Boston University course
 - Basic Concept/Specification by EC327 faculty
 - Figlets library by Sri Lakshmi Kanthan P (github: srilakshmikanthanp)
