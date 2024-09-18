#include "observer.h"
#include "cell.h"

// Constructor intialisation
Cell::Cell() : r{0}, c{0} {}

bool Cell::getState() const { return isOn; }
int Cell::getRow() const { return r; }
int Cell::getCol() const { return c; }

void Cell::setOn() {
  if (!isOn) { // go through this only if the cell is on
    isOn = true;
    notifyAllObservers(); // notifying observerss when the state of cell changes
  }
}

void Cell::toggle() {
  isOn = !isOn;
  notifyAllObservers(); // notify all observers about the state change
  notifySwitchObservers(); // notifying neighbours to toggle as well
}

void Cell::setCoords(int r, int c) { this->r = r; this->c = c; }

void Cell::attach(Observer *o) {
  observers.push_back(o);
}

// My neighbours will call this, to let me know they've been switched.
// Reference to notifier passed in so can obtain its state if needed.
void Cell::notify(Cell &) {
  toggle();
}

SubscriptionType Cell::subType() {
  return SubscriptionType::SwitchOnly;
}

// Alert observers whose subType is All. Tell the display my new state.
void Cell::notifyAllObservers() {
  for (Observer* observer : observers) {
        if (observer->subType() == SubscriptionType::All) {
            observer->notify(*this); // notify the observer providing this cell as the caller
        }
    }
}

// Alert observers whose subType is Switch. Tell all of my neighbours
// that I have been switched.
void Cell::notifySwitchObservers() {
   for (Observer* observer : observers) {
        if (observer->subType() == SubscriptionType::SwitchOnly) {
            observer->notify(*this); // notify the observer providing this cell as the caller
        }
    }
}
