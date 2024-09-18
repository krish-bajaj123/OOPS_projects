#include "Playlist.h"
#include "DigitalMedia.h"

//Cunstructor initialising the iterator ith the current node and elapsed time time set to
Playlist::Iterator::Iterator(Node *node , int getElapsedTime) : current(node), elapsedTime(0) {} 


DigitalMedia * Playlist::Iterator::operator*() const { 
    if (current != nullptr) {
        return current->item; // returns the DigitalMedia* in the Node struct if not null
    }
    return nullptr;
}

Playlist::Iterator& Playlist::Iterator::operator++() { 
    if (current != nullptr) {
        elapsedTime += current->item->getDuration(); // add time of current itrm to elapsed time
        current = current->next; // Move to the next Node in the Playlist.
    }
    return *this;
}

bool Playlist::Iterator::operator!=(const Playlist::Iterator &other) const {
    return current != other.current; // comparing the position of iterators
}   

int  Playlist::Iterator::getElapsedTime() const {
    return elapsedTime; // Rreturns the toal time of the media traversed by the iterator
}

Playlist::Node::Node(DigitalMedia* item, Playlist::Node* next) 
    : item{item}, next{next} {}

Playlist::Node::~Node() { delete next; }

Playlist::Iterator Playlist::begin() const { return Playlist::Iterator{front, 0}; }
Playlist::Iterator Playlist::end() const { return Playlist::Iterator{nullptr, 0}; }

Playlist::Playlist() 
    : front{nullptr}, back{nullptr}, secondsPlayedSoFar{0}, totalSeconds{0} {}

Playlist::~Playlist() { delete front; }
void Playlist::reset() { secondsPlayedSoFar = 0; } 
int Playlist::getTotalSeconds() const { return totalSeconds; }

void Playlist::add( DigitalMedia* m ) { 
    if ( front == back && front == nullptr ) {
        front = new Node{m};
        back = front;
        totalSeconds += m->getDuration();
        return;
    } // if

    Node* tmp = new Node{m};
    back->next = tmp;
    back = tmp;
    totalSeconds += m->getDuration();
} // Playlist::add

void Playlist::remove( DigitalMedia* m ) {
    // Is the list empty?
    if ( front == back && front == nullptr ) return;

    // Is it the first item? Keep going until end since might have
    // multiple instances in the play list. Stop if find item it isn't.
    while ( front->item == m ) {
        // Are we looking at the only item?
        if ( front == back && front->item == m ) {
            delete front;
            front = back = nullptr;
            totalSeconds = 0;
            return;
        } // if

        Playlist::Node* tmp = front;
        front = front->next;
        // Ensure don't delete rest of list.
        tmp->next = nullptr; 
        totalSeconds -= m->getDuration();
        delete tmp;
    } // while

    // If we get here, the first item in the list isn't the one we want.
    // Must find the item in the list. Keep going until end since might have
    // multiple instances in the play list.
    Playlist::Node* prev = front;
    Playlist::Node* cur  = front->next;

    while ( cur != nullptr ) {
        if ( cur->item == m ) {
            totalSeconds -= m->getDuration();
            Playlist::Node* tmp = cur;

            // If this is the last item, move the back pointer to the previous
            // item.
            if ( back == cur ) back = prev;

            // Make previous node point past this node to whatever is next.
            prev->next = cur->next;
            // Can't access node's next field properly if deleted.
            cur = cur->next; 
            // Ensure don't delete rest of list.
            tmp->next  = nullptr;
            delete tmp;
        } else {
            prev = cur;
            cur = cur->next;
        } // if   
    } // for
} // Playlist::remove

std::ostream & operator<<( std::ostream& out, const Playlist& p ) {
    unsigned int i = 1;
    for ( auto elem : p ) {
        out << '\t' << i << ": ";
        elem->print( out );
        out << std::endl;
        ++i;
    } // for

    out << "Total: " << p.getTotalSeconds() << " seconds" << std::endl;
    return out;
} // operator<<
