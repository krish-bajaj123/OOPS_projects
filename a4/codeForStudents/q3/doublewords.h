#ifndef DOUBLEWORDS_H
#define DOUBLEWORDS_H

#include "decorator.h"

// DoubleWords is a decorator that extents the functionality for doubling each word
class DoubleWords : public Decorator {
    std::string currentWord; // Stores the current word to possibly repeat it
    bool repeatWord = false; //  A flag used to see if the currentWord should be repeated or not
public:
    DoubleWords(TextProcessor *component); // constructs an DoubleWords decorator with a given TextProcessor component
    std::string getWord() override; // fetches a word from TextProcessor component and doubles it
};

#endif
