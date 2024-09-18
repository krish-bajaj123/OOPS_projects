#include "doublewords.h"

// Constructor intialisation
DoubleWords::DoubleWords(TextProcessor *component): Decorator(component) {}

std::string DoubleWords::getWord() {
    // flips repeatWord and returns the currentWord if it is repeating
    if (repeatWord) {
        repeatWord = false;
        return currentWord;
    } else {
        try {
            currentWord = component->getWord(); // Attempts to fetch of word
            repeatWord = true;
        } catch (const std::ios::failure&) {
            throw; // If an exception is caught rethrow the error to signal EOF
        }
        return currentWord;
    }
}
