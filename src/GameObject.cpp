#include "../inc/GameObject.hpp"


// STRUCTORS (Abstract Base Class)..............................................

GameObject::GameObject(char in_code) {
  display_code = in_code;
  id_num       = 1;      // NOTE: Currently, must be 1 digit wide for display...
  state        = '0';
  cout << "\nGameObject constructed,   ";
}

GameObject::GameObject(char in_code, int in_id, Point2D in_loc) {
  display_code = in_code;
  id_num       = in_id;
  location     = in_loc;
  state        = '0';
  cout << "\nGameObject constructed,   ";
}

GameObject::~GameObject() {
  cout << "GameObject destructed\n";
}


// MEMBER FUNCTIONS.............................................................

// Prints status of game objects; generally call after Model.Update()
void GameObject::ShowStatus() {                                       // Virtual
  cout << " " << display_code << id_num << " at " << location << endl;
}

// Draws objects on the game board, which is drawn by View.cpp
void GameObject::DrawSelf(char* ptr) {
  if (ptr[0] != '.') {
    ptr[0] = '*';
    ptr[1] = ' ';
  }
  else {
    ptr[0] = display_code;
    char id_number = '0'+id_num;           // Allows conversion from int to char
    ptr[1] = id_number;
  }
}


// GETTERS......................................................................

Point2D GameObject::GetLocation() { return location; }

int     GameObject::GetID()       { return id_num;   }

char    GameObject::GetState()    { return state;    }
