#include "Song.h"
#include "util.h"
#include <iostream>
#include <sstream>

// Constructor
Song::Song(const std::string & key, const std::string & title, int duration,
           const std::string & artist, const std::string & album, const std::string & genre)
    : DigitalMedia(key, title, duration), artist(artist), album(album), genre(genre) {
    if (key.length() < 1) std::cerr << "key has length < 1\n";
    if (title.length() < 1) std::cerr << "title has length < 1\n";
    if (duration < 1) std::cerr << "duration < 1\n";
    if (artist.length() < 1) std::cerr << "artist has length < 1\n";
    if (album.length() < 1) std::cerr << "album has length < 1\n";
    if (genre.length() < 1) std::cerr << "genre has length < 1\n";
}

// Destructor
Song::~Song() {
    // this will be empty because there is no dynamic memory to free
}

// Print method
void Song::print(std::ostream &out) const {
    out << *this;
}

const std::string &Song::getArtist() const {
    return artist;
}

const std::string &Song::getAlbum() const {
    return album;
}

const std::string &Song::getGenre() const {
    return genre;
}

// Output stream operator
std::ostream &operator<<(std::ostream &out, const Song &s) {
    out << "(" << s.getKey() << ", \"" << s.getTitle() << "\", \"" << s.getAlbum()
        << "\", \"" << s.getArtist() << "\", " << s.getDuration() << ", \"" << s.getGenre() << "\")";
    return out;
}

//Input stream operator
std::istream &operator>>(std::istream &in, Song &s) {
    std::string key, title, artist, album, genre;
    int duration;

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
    if (!getString(in, artist)) {
        std::cerr << "failed to read in artist" << std::endl;
        return in;
    }
    if (!getString(in, album)) {
        std::cerr << "failed to read in album" << std::endl;
        return in;
    }
    if (!getString(in, genre)) {
        std::cerr << "failed to read in genre" << std::endl;
        return in;
    }
    // if  all fields valid 
    s = Song(key, title, duration, artist, album, genre);
    return in;
}
