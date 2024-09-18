#include "TV.h"
#include "util.h"
#include <iostream>
#include <sstream>

// Constructor
TV::TV(const std::string & key, const std::string & title, int duration, int episode, int season, const std::string & series)
       :DigitalMedia(key, title, duration), episode(episode), season(season), series(series) {
    if (key.length() < 1) std::cerr << "key has length < 1\n";
    if (title.length() < 1) std::cerr << "title has length < 1\n";
    if (duration < 1) std::cerr << "duration < 1\n";
    if (season < 1) std::cerr << "season < 1\n";
    if (episode < 1) std::cerr << "episode < 1\n";
    if (series.length() < 1) std::cerr << "series has length < 1\n";
}

// Destructor
TV::~TV() {
    // this will empty because there is no memory to free
}

// Print method
void TV::print (std::ostream &out) const {
    out << *this;
}

// Accessor methods
int TV::getEpisode() const {
    return episode;
}

int TV::getSeason() const {
    return season;
}

const std::string &TV::getSeries() const {
    return series;
}

// Output stream operator
std::ostream &operator<<(std::ostream &out, const TV &t) {
    out<<"(" << t.getKey() << ", \"" << t.getSeries() << "\" S" << t.getSeason() 
        << "E" << t.getEpisode() << " \"" << t.getTitle() << "\", " << t.getDuration() << ")";
    return out;
}

// Input stream operator
std::istream &operator>>(std::istream &in, TV &t) {
    std::string key, title, series;
    int duration, season, episode;
    // Use utility functions to attempt to read inputs. If any read fails, log an error.
    if (!getString(in, key)) {
        std::cerr << "failed to read in key" << std::endl;
        return in;
    }
    if (!getString(in, title)) {
        std::cerr << "failed to read in title" << std::endl;
        return in;
    }
    if (!getInteger(in, duration)) {
        std::cerr << "failed to read in duration" << std::endl;
        return in;
    }
    if (!getInteger(in, season)) {
        std::cerr << "failed to read in season" << std::endl;
        return in;
    }
    if (!getInteger(in, episode)) {
        std::cerr << "failed to read in episode" << std::endl;
        return in;
    }
    if (!getString(in, series)) {
        std::cerr << "failed to read in series" << std::endl;
        return in;
    }
    // Since all inputs are successfully retrieved, update the TV object.
    t = TV(key, title, duration, episode, season, series);
    return in;
}

