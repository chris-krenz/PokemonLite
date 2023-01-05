#ifndef INPUT_HANDLING_HPP_
#define INPUT_HANDLING_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;


class Invalid_Input {
 public: 
  Invalid_Input(string in_ptr) : msg_ptr(in_ptr) {
    cin.clear();
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
  }
  const string msg_ptr;

 private:
   Invalid_Input();

};

#endif
