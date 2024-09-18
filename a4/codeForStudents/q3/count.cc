#include "count.h"

// Consturctor intialisation
Count::Count(TextProcessor *component, char c) : Decorator(component), target(c) {}

std::string Count::getWord() {
    std::string word;
    try {
        word = component->getWord(); // Attempts to fetch the next word
    } catch (const std::ios::failure&) {
        // If an exception is caught rethrow the error to signal EOF
        throw;
    }

    std::string result;
    for (char ch : word) {
        if (ch == target) {
            ++count; // Increments the count for target charcter
            result += std::to_string(count);
        } else {
            result += ch;
        }
    }
    return result;
}
