#ifndef ALLCAPS_H
#define ALLCAPS_H

#include "decorator.h"

// Constants for ASCII conversion
constexpr char lowercase_a = 'a';
constexpr char lowercase_z = 'z';
constexpr char diff = 'a' - 'A';

// AllCaps is a decorator class that converts all letters in the string to uppercase.
// It extends the decorator class and overrides the getWord method to implement this functionality.
class AllCaps : public Decorator {
public:
    AllCaps(TextProcessor *component); // constructs an AllCaps decorator with a given TextProcessor component
    std::string getWord() override; // fetches a word and converts it to uppercase
};

#endif
