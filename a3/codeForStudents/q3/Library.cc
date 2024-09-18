#include "Library.h"
#include "Song.h"
#include "TV.h"

// Constructor intialisation of an iterator to point to a specific node in the
Library::Iterator::Iterator(Node* node) : current(node) {}


DigitalMedia* Library::Iterator::operator*() const {
    return current ? current->media : nullptr;// return the media it holds otherwise nulllptr
}

Library::Iterator& Library::Iterator::operator++() { 
    if (current) current = current->next;// moves to the next node
    return *this;
}

bool Library::Iterator::operator!=(const Library::Iterator& other) const { 
    return current != other.current;// compares the current nodes of two iterators
} 

Library::Node::Node(const std::string& key, DigitalMedia* media, Node * next) 
    : key{key}, media{media}, next{next} {}

Library::Node::~Node() { delete media; delete next; }

Library::Library() : media{nullptr} {}
Library::~Library() { delete media; }

Library::Iterator Library::begin() const { return Library::Iterator{ media }; }
Library::Iterator Library::end() const { return Library::Iterator{ nullptr }; }

void Library::add( DigitalMedia* m ) {
    std::string key = m->getKey();
    Node * tmpN = new Node{ key, m, nullptr };
    DigitalMedia *item = find( key );

    if ( item != nullptr ) {
        std::cerr << "key " << key << " already exists in library" << std::endl;
        delete tmpN;
        return;
    }
    if ( media == nullptr || key < media->key ) {
        tmpN->next = media;
        media = tmpN;
    } else {
        Node * prev = media;
        Node * ptr = media->next;
        while ( ptr != nullptr && key > ptr->key ) {
            prev = ptr;
            ptr = ptr->next;
        }
        tmpN->next = ptr;
        prev->next = tmpN;
    }
} // Library::add


// Remove item if find key value else does nothing.
void Library::remove( const std::string& key ) {
    if ( media == nullptr ) return;
    if ( media->key == key ) {
        Node * tmp = media;
        media = media->next;
        tmp->next = nullptr; // ensure don't delete rest of list
        //delete tmp->media;
        delete tmp;
        return;
    }

    Node * prev = media;
    Node * ptr = media->next;
    while ( ptr != nullptr ) {
        if ( key == ptr->key ) {
            Node * tmp = ptr;
            prev->next = ptr->next;
            tmp->next = nullptr;
            //delete tmp->media;
            delete tmp;
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
} // Library::remove

// Returns pointer to item, or nullptr if not there.
DigitalMedia * Library::find( const std::string& key ) const {
    for ( Node * ptr = media; ptr != nullptr; ptr = ptr->next ) {
        if ( ptr->key == key ) return ptr->media;
    }
    return nullptr;
} // Library::find

std::ostream& operator<<( std::ostream& out, Library& library ) {
    out << "Library:" << std::endl;    
    for ( Library::Iterator it = library.begin(); it != library.end(); ++it ) {
        out << '\t'; (*it)->print(out); out << std::endl;
    }
    return out;
} // operator<<

std::istream& operator>>( std::istream& in, Library& library ) {
    // dummy values used to help read in info.
    TV t1{ "TV01", "Somewhere far away, and long ago", 42*60, 1, 1, "Amazing New Show" };
    Song s1{ "S01", "Great beat and you can dance to it", 183, "Too cool", 
        "I'd give it a 10!", "Eclectic" };
    std::string line;
    char mediaType;
    while ( true ) {
        in >> mediaType;
        if ( in.fail() ) break;
        getline( in, line ); // throw away rest of line
        if ( mediaType == 's' ) {
            in >> s1;
            library.add( new Song{s1} );
        } else if ( mediaType == 't' ) {
            in >> t1;
            library.add( new TV{t1} );
        } else {
            std::cerr << "invalid media type " << mediaType << std::endl;
        } // if
    } // while
    return in;
} // operator>>
