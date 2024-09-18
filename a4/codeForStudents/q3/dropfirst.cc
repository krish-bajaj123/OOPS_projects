#include "dropfirst.h"

//Constructor intialisation
DropFirst::DropFirst(TextProcessor* component, int n) : Decorator(component), n(n) {}

std::string DropFirst::getWord() {
    std::string word;
    while (true) {
        try {
            word = component->getWord(); // Attempts to fetch the next word
            // If the length of word is greater than n, drop first n charcters
            if (word.length() > (std::size_t)n) {
                return word.substr(n);
            }
            // If the word is shorter than n charcters , it will fetch the next word
        } catch (const std::ios::failure&) {
            throw; // If an exception is caught rethrow the error to signal EOF
        }
    }
}
