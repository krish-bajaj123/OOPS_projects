#include "tierlist.h"
#include <utility>

void TierList::swap(TierList &other) {
  std::swap(tiers, other.tiers);
  std::swap(tierCount, other.tierCount);
  std::swap(reserved, other.reserved);
}

void TierList::enlarge() {
  reserved = 2 + 2 * std::max(reserved, tierCount);
  List **newTiers = new List *[reserved];
  std::fill_n(newTiers, reserved, nullptr);
  std::copy_n(tiers, tierCount, newTiers);
  delete[] tiers;
  tiers = newTiers;
}

TierList::TierList() : tiers{nullptr}, tierCount{0}, reserved(0) {}
TierList::~TierList() {
  if (tiers) {
    for (size_t i = 0; i < tierCount; ++i) {
      delete tiers[i];
    }
  }
  delete[] tiers;
}

void TierList::push_back_tier() {
  // Need at least 1 extra as sentinel.
  if (tierCount + 1 >= reserved) {
    enlarge();
  }
  tiers[tierCount++] = new List;
}
void TierList::pop_back_tier() {
  if (tierCount > 0) {
    delete tiers[--tierCount];
    tiers[tierCount] = nullptr;
  }
}

void TierList::push_front_at_tier(size_t tier, const std::string &entry) {
  tiers[tier]->push_front(entry);
}
void TierList::pop_front_at_tier(size_t tier) {
  tiers[tier]->pop_front();
}

size_t TierList::tierSize() const { return tierCount; }
size_t TierList::size() const {
  size_t result = 0;
  for (size_t i = 0; i < tierCount; i++) {
    result += tiers[i]->size();
  }
  return result;
}

TierList::iterator::iterator(const TierList *list, size_t tier, List::iterator pos)
  : tierList(list), currenttier(tier), currentelement(pos) {}


TierList::value_type TierList::iterator::operator*() const {
    return {currenttier, *currentelement};
}

TierList::iterator & TierList::iterator::operator++() {
    // If not end of list move to next element
    if (++currentelement != tierList->tiers[currenttier]->end()) {
        return *this; // Successfully moved to next element within tier.
    }
    // Move to next tier keeping tier boundary in mind
    while (++currenttier < tierList->tierCount) {
        currentelement = tierList->tiers[currenttier]->begin();
        if (currentelement != tierList->tiers[currenttier]->end()) {
            return *this; // non-empty tier.
        }
    }
    return *this; // End of TierList.
}

TierList::iterator TierList::iterator::operator<<(int bk) const {
    int newtier = int(currenttier);
    while (bk > 0 && newtier >= 0) {
        --newtier;
        bk--;
        // Skip empty tiers
        while (newtier >= 0 && tierList->tiers[newtier]->size() == 0) {
            --newtier;
        }
    }
    // Check for tier start
    if (newtier < 0) {
        newtier = 0;
    }
    return TierList::iterator(tierList, size_t(newtier), tierList->tiers[newtier]->begin());
}

TierList::iterator TierList::iterator::operator>>(int fwd) const {
    size_t newTier = currenttier + fwd; // Attempt to move forward in tiers
    // exceeds tierCount
    if (newTier >= tierList->tierCount) {
        return tierList->end();
    }
    // Find the next non-empty tier
    while (newTier < tierList->tierCount && tierList->tiers[newTier]->size() == 0) {
        ++newTier; // Skip empty tiers
        if (newTier >= tierList->tierCount) {
            return tierList->end();
        }
    }
    // Return iterator to selected tier
    return TierList::iterator(tierList, newTier, tierList->tiers[newTier]->begin());
}

bool TierList::iterator::operator!=(const iterator &other) const {
  // Compare based on the tierList pointer, currentTier, and the position within the List
    return tierList != other.tierList || currenttier != other.currenttier ||
           currentelement != other.currentelement;
}

TierList::iterator TierList::begin() const {
   for (size_t i = 0; i < tierCount; ++i) {
        if (tiers[i]->begin() != tiers[i]->end()) {
            // if we Found a non-empty tier, we return its beginning
            return iterator(this, i, tiers[i]->begin());
        }
    }
    // If all tiers are empty or there are no tiers, return end()
    return this->end();
}


TierList::iterator TierList::end() const {
    return iterator(this, tierCount, List().end());
}

