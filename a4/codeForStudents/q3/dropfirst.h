#ifndef DROPFIRST_H
#define DROPFIRST_H

#include "decorator.h"

// DropFirst is a decorator that extents the functionality for droping n number of charcters from the word
class DropFirst : public Decorator {
    int n; // number of charcters that need to be dropped
public:
    DropFirst(TextProcessor* component, int n); // constructs an DropFirst decorator with a given TextProcessor component
    std::string getWord() override; // fetches a word from TextProcessor component and removes n number of charcters from 
                                    // the word.
};

#endif
