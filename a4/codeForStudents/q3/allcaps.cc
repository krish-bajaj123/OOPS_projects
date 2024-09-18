#include "allcaps.h"

// Constructor inittialisation
AllCaps::AllCaps(TextProcessor *component) : Decorator(component) {}

std::string AllCaps::getWord() {
    std::string word;
    try {
        word = component->getWord(); // attempt to fetch a word
    } catch (const std::ios::failure&) {
        // If an exception is caught rethrow the error to signal EOF
        throw;
    }
    // convert lowercase letters to uppercase
    for (char &c : word) {
        if (c >= lowercase_a && c <= lowercase_z) {
            c -= diff; // Convert to uppercase
        }
    }
    return word;
}
