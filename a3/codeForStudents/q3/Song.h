#ifndef SONG_H
#define SONG_H

#include "DigitalMedia.h"

class Song: public DigitalMedia {
    std::string artist;  // artist of the piece
    std::string album;   // album that the piece is contained within, if applicable
    std::string genre;   // genre, if applicable
public:
    // Sets key, title, duration, artist, album, and genre information.
    // If key.length() < 1 outputs to stderr: "key has length < 1".
    // If title.length() < 1 outputs to stderr: "title has length < 1".
    // If duration < 1 outputs to stderr: "duration < 1".
    // If artist.length() < 1 outputs to stderr: "artist has length < 1"
    // If album.length() < 1 outputs to stderr: "album has length < 1"
    // If genre.length() < 1 outputs to stderr: "genre has length < 1"
    // (Checks are made in order listed.)
    Song( const std::string & key, const std::string & title, int duration,
         const std::string & artist, const std::string & album, const std::string & genre );
    virtual ~Song();
    virtual void print( std::ostream & out ) const override;

    const std::string & getArtist() const;
    const std::string & getAlbum() const;
    const std::string & getGenre() const;
};

// Returns modified output stream. Outputs (key, "title", "album", "artist", duration, "genre").
// (Explicitly surrounds strings that might have whitespace within with double-quotation marks.)
std::ostream & operator<<( std::ostream & out, const Song & s );

// Returns modified input stream. Contents of s over-written with information read in, where
// format is "key\ntitle\nduration\nartist\nalbum\ngenre\n". 
// If fails to obtain any of the elements, outputs the message "failed to read in XXX", where XXX is 
// replaced by one of: key, title, duration, artist, album, or genre or 
// if duration cannot be successfully converted to an int.
std::istream & operator>>( std::istream & in, Song & s );

#endif
