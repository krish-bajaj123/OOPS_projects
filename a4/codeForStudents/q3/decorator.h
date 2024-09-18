#ifndef DECORATOR_H
#define DECORATOR_H

#include "textprocess.h"

// Decorator is an abstract class that uses the decorator design pattern
class Decorator : public TextProcessor {
protected:
    TextProcessor *component; // constructor that initialises the decorator with a specific TextProcessor component
public:
    Decorator(TextProcessor *component): component(component) {}
    virtual ~Decorator() { delete component; } // destructor used for deleting the component
    void setSource(std::istream *in) override { // sets the source of input for TextProcessor
        component->setSource(in);
    }
};

#endif
