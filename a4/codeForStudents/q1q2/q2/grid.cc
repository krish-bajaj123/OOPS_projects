#include <iostream>
#include "grid.h"
using namespace std;

// Constructor intialisation
Grid::Grid() : gridSize{0} , td{nullptr} , gd{nullptr} {}

//Destructor
Grid::~Grid() {
  delete td;
  delete gd;
}

// Frees the grid.
void Grid::clearGrid() {
  if (!theGrid.empty()) {
        theGrid.clear();
        gridSize = 0;
    }
}

// Returns whether or not grid is in a winning state.
bool Grid::isWon() const { 
  for (const auto &row : theGrid) {
        for (const auto &cell : row) {
            if (cell.getState()) {
                return false; // Lost , when found a cell was not on
            }
        }
    }
    return true; // Won when all cells are on
}

// Sets up an n x n grid.  Clears old grid, if necessary.
void Grid::init(int n) {
   clearGrid(); // Clear existing grid 
    gridSize = n;
    theGrid.resize(n, std::vector<Cell>(n)); // Create a grid of size n x n
    
    delete td; // Safely delete and recreate the text display
    td = new TextDisplay(n);
    delete gd;
    gd = new GraphicsDisplay(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            theGrid[i][j].setCoords(i, j); // Initialize cell coordinates
            theGrid[i][j].attach(td); // Attach the display as an observer, if necessary
            theGrid[i][j].attach(gd); // Additionally, attach GraphicsDisplay as observer
        }
    }
}

// Sets cell at row r, col c to On.
void Grid::turnOn(int r, int c) {
  if (r >= 0 && r < gridSize && c >= 0 && c < gridSize) {
        theGrid[r][c].setOn();
    }
}

// Toggles cell at row r, col c.
void Grid::toggle(int r, int c) {
  // Bounds checking
    if (r < 0 || r >= gridSize || c < 0 || c >= gridSize) return;
    // Toggle the specified cell
    theGrid[r][c].toggle();
    // Notify the above neighbor
    if (r > 0) {
        theGrid[r - 1][c].notify(theGrid[r][c]);
    }
    // Notify the below neighbor
    if (r < gridSize - 1) {
        theGrid[r + 1][c].notify(theGrid[r][c]);
    }
    // Notify the left neighbor
    if (c > 0) {
        theGrid[r][c - 1].notify(theGrid[r][c]);
    }
    // Notify the right neighbor
    if (c < gridSize - 1) {
        theGrid[r][c + 1].notify(theGrid[r][c]);
    }
}

// Overloads the << operator for printing the Grid object to an output stream
ostream &operator<<(ostream &out, const Grid &g) {
  if (g.td != nullptr) {
        out << *(g.td);
    }
    return out;
}
