#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>

class DigitalMedia; // forward declaration

class Playlist {
    struct Node; // forward declaration

  public:

    class Iterator {
        friend class Playlist;
        Node* current;
        int elapsedTime;

        // Private constructor, accessible only by the Playlist.
        Iterator(Node* node, int elapsed);

      public:
        int getElapsedTime() const;   

        // Caller "plays" the item by printing its information to std::cout.
        DigitalMedia* operator*() const;

        // Adds the duration of the item just played to the total time elapsed so far before moving
        // the iterator.
        Iterator& operator++();

        bool operator!=(const Iterator &other) const; 
    };

    Playlist();
    virtual ~Playlist();
    void reset(); // resets the elapsed time back to 0
    void add( DigitalMedia* m );
    void remove( DigitalMedia* m );
    Iterator begin() const;
    Iterator end() const;
    int getTotalSeconds() const;

  private:

    struct Node {
        friend class Playlist::Iterator;
        DigitalMedia* item;
        Node* next;
        Node(DigitalMedia* item, Node* next = nullptr);
        ~Node();
    };

    Node* front;
    Node* back;
    int secondsPlayedSoFar;
    int totalSeconds;

};

std::ostream & operator<<( std::ostream& out, const Playlist& p );

#endif
