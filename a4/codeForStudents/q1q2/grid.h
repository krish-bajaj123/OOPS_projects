#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "cell.h"
#include "textdisplay.h"

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  int gridSize;    // Size of the grid.
  TextDisplay *td; // The text display.
  // Add private members, if necessary.

  void clearGrid();   // Frees the grid.

 public:
  Grid(); // Grid is initially 0x0
  ~Grid();
  
  bool isWon() const; // Returns whether or not grid is in a winning state.
  void init(int n); // Sets up an n x n grid.  Clears old grid, if necessary.
  void turnOn(int r, int c);  // Sets cell at row r, col c to On.
  void toggle(int r, int c);  // Toggles cell at row r, col c.
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
