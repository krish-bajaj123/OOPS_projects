#ifndef COUNT_H
#define COUNT_H

#include "decorator.h"
#include <string>

// Count is a decorator class that helps us replace the number
// of occcurences of the target charcter with their occurence number.
class Count : public Decorator {
    char target; // The character to count and replace
    int count; // Directly track the count of the target character
public:
    Count(TextProcessor *component, char target); // constructor for count decorator
    std::string getWord() override; // fetches a word from the TextProcessor component and replace the number
                                    // of occcurences of the target charcter with their occurence number.
};

#endif
