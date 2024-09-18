// GraphicsDisplay.h
#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "observer.h"
#include "window.h"
#include <vector>

class GraphicsDisplay: public Observer {
    Xwindow xw;
    int gridSize;
    int cellSize; // Size of each cell in pixels
public:
    GraphicsDisplay(int gridSize);
    void notify(Cell &c) override;
    SubscriptionType subType() override;
    ~GraphicsDisplay() override = default;
};

#endif
