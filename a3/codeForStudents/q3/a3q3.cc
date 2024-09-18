#include "TV.h"
#include "Song.h"
#include "Library.h"
#include "Playlist.h"
#include "util.h"
#include <fstream>

const int MAX_NUM_PLAYLISTS = 5;

void testSongCtor() {
    std::string key, title, artist, album, genre;
    int duration;
    bool readSucceeded = true;

    readSucceeded &= getString( std::cin, key );
    if ( readSucceeded ) readSucceeded &= getString( std::cin, title );
    if ( readSucceeded ) readSucceeded &= getInteger( std::cin, duration );
    if ( readSucceeded ) readSucceeded &= getString( std::cin, artist );
    if ( readSucceeded ) readSucceeded &= getString( std::cin, album );
    if ( readSucceeded ) readSucceeded &= getString( std::cin, genre );
    if ( readSucceeded ) Song{ key, title, duration, artist, album, genre };
} // testSongCtor

void testTVCtor() {
    std::string key, title, series;
    int duration, season, episode;
    bool readSucceeded = true;

    readSucceeded &= getString( std::cin, key );
    if ( readSucceeded ) readSucceeded &= getString( std::cin, title );
    if ( readSucceeded ) readSucceeded &= getInteger( std::cin, duration );
    if ( readSucceeded ) readSucceeded &= getInteger( std::cin, season );
    if ( readSucceeded ) readSucceeded &= getInteger( std::cin, episode );
    if ( readSucceeded ) readSucceeded &= getString( std::cin, series );

    if ( readSucceeded ) TV{ key, title, duration, season, episode, series };
} // testTVCtor

int main() {
    // Initial dummy values for a song and a TV show to facilitate reading in information
    // over top of an existing object.
    TV t1{ "TV01", "Somewhere far away, and long ago", 2580, 1, 1, "Amazing New Show" };
    Song s1{ "S01", "Great beat and you can dance to it", 183, "Too cool", 
        "I'd give it a 10!", "Eclectic" };

    Playlist plists[MAX_NUM_PLAYLISTS];
    Playlist * curPList = nullptr;
    Playlist::Iterator it = plists[0].begin(); // initial dummy value so can declare variable
    Library media;
    DigitalMedia *mptr = nullptr;
    char command, dmtype, arg;
    std::string line, key, filename;
    int index = 0;

    while ( true ) {
        std::cin >> command;

        // Terminate the program if enter 'q' or reach EOF.
        if ( std::cin.fail() || command == 'q' ) break;

        switch( command ) {
            case 'c':
                // "c t" tests the TV constructor.
                // "c s" tests the Song constructor.
                std::cin >> arg;
                getline( std::cin, line ); // throw away rest of line.
                if ( arg == 't' ) { testTVCtor(); } 
                else if ( arg == 's' ) { testSongCtor(); }
                break;

            case 'p':
                // "p m" prints the contents of the media library.
                // "p p <idx>" prints the contents of the playlist at index <idx>
                std::cin >> arg;
                if ( arg == 'm' ) { 
                    std::cout << media;
                } else if ( arg == 'p' ) {
                    std::cin >> index;
                    if ( index >= 0 && index < MAX_NUM_PLAYLISTS ) {
                        std::cout << "Playlist[" << index <<"]:\n" << plists[index];
                    }
                } // if 
                break;

            case 'r':
                // "r <key>" removes all items with the specified key from the media library
                // and from all playlists. Silently does nothing if such an item doesn't exist.
                std::cin >> key;
                mptr = media.find( key );
                if ( mptr ) { 
                    for ( int i = 0; i < MAX_NUM_PLAYLISTS; i++ ) {
                        plists[i].remove( mptr );
                    }
                    media.remove( key );
                } // if
                break;

            case '>':
                // Precondition: "f p <idx>" must have been executed first
                // If has a current playlist and haven't reached the end, "play" the current media
                // item by printing its information, and how much time in the playlist has elapsed
                // out of the total time. Advances the iterator. 
                if ( curPList != nullptr && it != curPList->end() ) {
                    // Get item to "play" by printing item *after* advance iterator to 
                    // increment elapsed time.
                    mptr = *it; 
                    ++it;       
                    mptr->print( std::cout );
                    std::cout  << " "<< it.getElapsedTime() << "/" 
                        << curPList->getTotalSeconds() << std::endl;
                } // if
                break;

            case 'z':
                // Resets the current playlist iterator to start over from the beginning.
                // Also resets the elapsed time to 0.
                if ( curPList != nullptr ) {
                    it = curPList->begin();
                    curPList->reset();
                } // if
                break;

            case 'f':
                // "f m <key>" looks for the item with the specified key in the media library.
                // "f p <idx>" sets the current playlist to the playlist at index <idx> and sets
                //    the play iterator to start at the beginning.
                std::cin >> arg;
                if ( arg == 'm' ) {
                    std::cin >> key;
                    mptr = media.find( key );
                    if ( mptr ) {
                        std::cout << "Found: ";
                        mptr->print( std::cout );
                        std::cout << std::endl;
                    } else {
                        std::cerr << "Library doesn't contain any item with key " 
                            << key << std::endl;
                    } // if
                } else if ( arg == 'p' ) { // sets current playlist, for use with play iterator
                    std::cin >> index;
                    curPList = nullptr;
                    if ( index >= 0 && index < MAX_NUM_PLAYLISTS ) {
                        curPList = &plists[index];
                        it = curPList->begin();
                    } // if
                } // if
                break;

            case 'i':
                {
                    // "i <filename>" inserts the contents of file <filename> into the media library.
                    // <filename> consists of a sequence of "a m" commands as described below.
                    std::cin >> filename;
                    getline( std::cin, line ); // throw away rest of line.
                    std::ifstream infile{ filename };
                    infile >> media; // operator>> for Library
                }
                break;

            case 'a':
                // "a m t\n" is used to add a TV show to a media library. The information that
                // follows must follow the format as specified for the operator>> for a TV show.
                // "a m s\n" is used to add a song to a media library. The information that
                // follows must follow the format as specified for the operator>> for a song.
                // "a p <idx> <key>" add the media item with key <key> to the playlist at index <idx>.
                // Silently fails if <idx> not in range [0, MAX_NUM_PLAYLISTS-1] or media library
                // doesn't contain an item with key <key>.
                std::cin >> arg;
                if ( arg == 'm' ) {
                    std::cin >> dmtype;
                    getline( std::cin, line ); // throw away rest of line
                    if ( dmtype == 't' ) {
                        std::cin >> t1; // operator>> for TV
                        media.add( new TV{t1} );
                    } else if ( dmtype == 's' ) {
                        std::cin >> s1; // operator>> for Song
                        media.add( new Song{s1} );
                    } else {
                        std::cerr << "invalid media type " << dmtype << std::endl;
                    } // if
                } else if ( arg == 'p' ) {
                    std::cin >> index >> key;
                    if ( index >= 0 && index < MAX_NUM_PLAYLISTS ) {
                        mptr = media.find( key );
                        if ( mptr ) plists[index].add( mptr );
                    } // if
                } // if
                break;
        } // switch
    } // while
} // main
