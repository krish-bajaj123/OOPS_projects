#include <iostream>
#include "textdisplay.h"
#include "cell.h"
using namespace std;

// Constructor intializes a TextDisplay oobject with a grid size of n * n
TextDisplay::TextDisplay(int n) : gridSize(n) {
  theDisplay.resize(n, std::vector<char>(n, '_'));
}

// The display updates the cell 'X' if on or this '_' when off
void TextDisplay::notify(Cell &c) {
  int row = c.getRow();
  int col = c.getCol();
  bool isOn = c.getState();

  theDisplay[row][col] = isOn ? 'X' : '_'; // 'X' for on, '_' for off
}

// Destructor
TextDisplay::~TextDisplay() {}

// Return the SubscriptionType of TextDisplay
SubscriptionType TextDisplay::subType() {
  return SubscriptionType::All;
}

// Overloads the operator << operator for the TextDisplay class
ostream &operator<<(ostream &out, const TextDisplay &td) {
   for (const auto &row : td.theDisplay) {
        for (const auto &cell : row) {
            out << cell;
        }
        out << endl; // New line at the end of each row
    }
    return out;
}
