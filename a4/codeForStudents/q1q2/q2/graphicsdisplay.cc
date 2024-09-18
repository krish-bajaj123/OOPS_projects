// GraphicsDisplay.cc
#include "graphicsdisplay.h"
#include "cell.h"

GraphicsDisplay::GraphicsDisplay(int gridSize): xw(500, 500), gridSize(gridSize) {
    cellSize = 500 / gridSize; // Assuming the window size is 500x500
}

void GraphicsDisplay::notify(Cell &c) {
    int x = c.getCol() * cellSize;
    int y = c.getRow() * cellSize;
    int color = c.getState() ? Xwindow::Black : Xwindow::White;
    xw.fillRectangle(x, y, cellSize, cellSize, color);
}

SubscriptionType GraphicsDisplay::subType() {
    return SubscriptionType::All; // Subscribe to all events
}
