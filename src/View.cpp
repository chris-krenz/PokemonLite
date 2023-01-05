#include "../inc/View.hpp"


// STRUCTORS

View::View() {  // Default loc: (0, 0)
  size  = 11;
  scale = 2;
  cout << "View constructed\n\n";
}

View::~View() {
  cout << "\nView destructed\n";
}


// FUNC SEQ (from Model): Clear, Plot, Draw.....................................

// Resets the grid after every time step
void View::Clear() {
  for   (int j = 0; j <= size - 1; j++) {
    for (int i = 0; i <= size - 1; i++) {
      grid[i][j][0] = '.';
      grid[i][j][1] = ' ';
    }
  }
}

// Calls draw self to put game objects on the grid
void View::Plot(GameObject* ptr) {
  int x, y;
  if (ptr->ShouldBeVisible()) {
    if (GetSubscripts(x, y, ptr->GetLocation())) {
      ptr->DrawSelf(grid[x][y]);
    }
  }
}

// Draws grid 2 wide at each cell (to fit object code + id, e.g. T1)
void View::Draw() {
  for   (int j = size-1; j >= -1;     j--) {
    for (int i = -1;     i <= size-1; i++) {
      if (i == -1 && j%2 == 0) {                //grid axis
        cout << j*2;
        if (j/5 == 0) {
          cout << " ";
        }
      } else if (i == -1 && j%2 != 0) {
        cout << "  ";
      } else if (j == -1 && i%2 == 0) {
        cout << i*2;
        if (i/5 == 0) {
          cout << " ";
        }
        cout << "  ";
      }
      if (i >= 0 && j >=0) {                    //draw objects
        cout << grid[i][j][0] << grid[i][j][1];
      }
    }
    cout << endl;
  }
}

// Called by Plot; gets exact grid location of objects...
bool View::GetSubscripts(int& out_x, int& out_y, Point2D location) {
  int x = (location.x - origin.x) / scale;
  int y = (location.y - origin.y) / scale;
  if (x < size && y < size) {
    out_x = x;
    out_y = y;
    return true;
  } else {
    cout << "** An object is outside the display! **\n";
    return false;
  }
}
