#ifndef TIER_LIST_H
#define TIER_LIST_H
#include "list.h"
#include <string>

class TierList {
  List **tiers; // dynamic array of (List*)
  size_t tierCount; // number of tiers (List*) in the tier list
  size_t reserved; // total possible number of tiers

  void swap(TierList &other);
  void enlarge();

 public:
  // Default constructor and destructor for a TierList.
  // The default constructor should initalize an empty tier list.
  TierList();
  ~TierList();

  // Adds/removes a tier at the end of the tier list.
  // Tiers are indexed starting at 0.  Runs in time
  // at most _linear in the number of tiers_, but _not_ in the number
  // of elements.
  void push_back_tier();
  void pop_back_tier();

  // Adds/removes an element at the front of the given tier.
  // Must run in constant time.
  void push_front_at_tier(size_t tier, const std::string &entry);
  void pop_front_at_tier(size_t tier);

  // Returns the number of tiers.  Runs in constant time.
  size_t tierSize() const;
  // Returns the number of elements.  Can run in time
  // up to linear in the number of tiers.
  size_t size() const;

 public:
  struct value_type {
    size_t tier;
    std::string entry;
  };
  class iterator {
    friend class TierList;
    const TierList *tierList;
    size_t currenttier;
    List::iterator currentelement;

    // Private constructor accessible only by TierList
    iterator(const TierList *list, size_t tier, List::iterator pos);
  public:
    // Returns a value_type instance, containing
    // - a) the tier the item that the iterator points to lives at.
    // - b) the item the iterator points to
    value_type operator*() const;

    // If the current tier isn't empty, moves to the next tier element; otherwise,
    // moves to the next non-empty tier in the tier list. If there is no such tier,
    // returns end().
    iterator &operator++();

    // New iterator operators which return a iterator pointing to the
    // start of the tier bk elements behind/fwd elements later
    // of the tier the iterator is currently on.
    //
    // If said tier is empty, the iterator moves back/forward to the next such
    // non-empty tier. If there is no such tier, returns end().
    iterator operator<<(int bk) const;
    iterator operator>>(int fwd) const;

    // Returns true if the two iterators are either not on the same tier list, or
    // not on the same element of the same tier list.
    bool operator!=(const iterator &other) const;
  };

  // Sets the iterator to the first element of the first non-empty tier. If there
  // is no such tier, returns end().
  iterator begin() const;
  // Returns an iterator that indicates the end of the tier list has been reached.
  iterator end() const;
};

#endif
