#include "DigitalMedia.h"

// Constructor
DigitalMedia::DigitalMedia(const std::string &key, const std::string &title, int duration)
    : key(key), title(title), duration(duration) {}

// Virtual destructor
DigitalMedia::~DigitalMedia() {
    // this will empty because there is no memory to free
}

// Print method
void DigitalMedia::print(std::ostream &out) const {
    out << *this;
}

// Accessor methods
const std::string &DigitalMedia::getKey() const {
    return key;
}

const std::string &DigitalMedia::getTitle() const {
    return title;
}

int DigitalMedia::getDuration() const {
    return duration;
}

// Output stream operator
std::ostream &operator<<(std::ostream &out, const DigitalMedia &s) {
    // Implementations in derived classes should handle their own specific output requirements.
    out << "(" << s.getKey() << ", \"" << s.getTitle() << "\", " << s.getDuration() << " seconds)";
    return out;
}
