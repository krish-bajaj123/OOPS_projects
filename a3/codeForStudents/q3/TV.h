#ifndef _TV_H
#define _TV_H

#include "DigitalMedia.h"

class TV: public DigitalMedia {
    int episode;          // episode number
    int season;           // season number
    std::string series;   // name of the televesion series
public:
    // Sets key, title, duration, episode, season, and series information.
    // If key.length() < 1 outputs to stderr: "key has length < 1".
    // If title.length() < 1 outputs to stderr: "title has length < 1".
    // If duration < 1 outputs to stderr: "duration < 1".
    // If season < 1 outputs to stderr: "season < 1"
    // If episode < 1 outputs to stderr: "episode < 1"
    // If series.length() < 1 outputs to stderr: "series has length < 1"
    // (Checks are made in order listed.)
    TV( const std::string & key, const std::string & title, int duration,
         int episode, int season, const std::string & series );
    virtual ~TV();
    virtual void print( std::ostream & out ) const override;

    int getEpisode() const;
    int getSeason() const;
    const std::string & getSeries() const;
};

// Returns modified output stream. Outputs (key, "series" S<season>E<episode> "title", duration).
// (Explicitly surrounds strings that might have whitespace within with double-quotation marks.
std::ostream & operator<<( std::ostream & out, const TV & t );

// Returns modified input stream. Contents of t over-written with information read in if valid, where
// format is "key\ntitle\nduration\nseason\nepisode\nseries\n". 
// If fails to obtain any of the elements, outputs the message "failed to read in XXX", where XXX is 
// replaced by one of: key, title, duration, season, episode, or series or 
// if duration, season, or episode cannot be successfully converted to an int.
std::istream & operator>>( std::istream & in, TV & t );

#endif
