#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>
#include <iostream>

class DigitalMedia; // forward declaration

class Library {
    // can be removed once add iterators to library and playlist
    friend std::ostream & operator<<( std::ostream & out, Library & lib );

    struct Node {
        std::string key;
        DigitalMedia* media;
        Node* next;
        Node(const std::string& key, DigitalMedia* media, Node* next = nullptr);
        ~Node();
    };
    Node* media;

  public:

    class Iterator {
        friend class Library;
        Node* current; // Pointer to the current node in the iteration

        // Private constructor, only accessible by Library
        Iterator(Node* node);

      public:
        DigitalMedia* operator*() const;
        Iterator& operator++();
        bool operator!=(const Iterator &other) const;    
    };

    Library();                       // Creates empty library.
    ~Library();                      // Destroys all items in library.
    Iterator begin() const;          // Iterator set to beginning of library contents.
    Iterator end() const;            // Iterator set past end of library contents.

    // Stores item, indexed by key. If key already exists outputs to stderr
    // "key KKKK already exists in library" and item not stored.
    void add( DigitalMedia* m );    

    // Remove item and delete media if find key value else does nothing.
    void remove( const std::string& key );  

    // Returns pointer to item, or nullptr if not there.
    DigitalMedia* find( const std::string& key ) const; 
};

// Returns modified output stream. Stream contains the header "Library:\n" and the library
// contents, ordered by key. Each object is output using the appropriate output operator
// for the underlying object type, one per line and starting with a tab character.
std::ostream& operator<<( std::ostream& out, Library& library );

// Returns modified input stream. Contents of library modified with information read in, 
// where the character 't' on a line specifies a TV show is to be read next, while 's'
// indicates that a Song is to be read in next. Reading continues until EOF is reached
// or an error is detected. Outputs "invalid media type" to stderr followed by what 
// type was read if doesn't get either 's' or 't'.
std::istream& operator>>( std::istream& in, Library& library );

#endif
