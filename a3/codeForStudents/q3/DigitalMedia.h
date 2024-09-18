#ifndef _DIGITAL_MEDIA
#define _DIGITAL_MEDIA

#include <string>
#include <iostream>

class DigitalMedia {
    std::string key;   // key that uniquely identifies the media
    std::string title; // title of the piece
    int duration;      // length of the media, in seconds
public:
    // Sets key, title and duration information.
    // If key.length() < 1 outputs to stderr: "key has length < 1".
    // If title.length() < 1 outputs to stderr: "title has length < 1".
    // If duration < 1 outputs to stderr: "duration < 1".
    // (Checks are made in order listed.)
    DigitalMedia( const std::string & key, const std::string & title, int duration );
    virtual ~DigitalMedia();

    // Concrete subclasses use this to invoke their output operator so that Library
    // container can successfully print its contents using the iterator.
    virtual void print( std::ostream & out ) const;

    const std::string & getKey() const;
    const std::string & getTitle() const;
    int getDuration() const;
};

// Returns modified output stream. Outputs (key, "title", "album", "artist", duration, "genre").
// (Explicitly surrounds strings that might have whitespace within with double-quotation marks.)
std::ostream & operator<<( std::ostream & out, const DigitalMedia & s );

#endif
