#include "DoganBank.h"

// Resource Functions
void DoganBank::addResource(const ResourceType r, const int n) {
    resources[static_cast<int>(r)] += n;
}
size_t DoganBank::getResourceCount(const ResourceType r) const {
    return resources[static_cast<int>(r)];
}
const std::array<size_t, 5> DoganBank::getResources(void) const {
    return resources;
}
void DoganBank::setResources(const std::array<size_t, 5> r) {
    resources = r;
}
void DoganBank::removeResource(const ResourceType r, const int n) {
    resources[static_cast<int>(r)] -= n;
}

// Development Functions
void DoganBank::addDevelopment(const DevelopmentType d) {
    developments[static_cast<int>(d)] += 1;
}
size_t DoganBank::getDevelopmentCount(const DevelopmentType d) const {
    return developments[static_cast<int>(d)];
}
const std::array<size_t, 5> DoganBank::getDevelopments(void) const {
    return developments;
}
void DoganBank::setDevelopments(const std::array<size_t, 5> d) {
    developments = d;
}
void DoganBank::removeDevelopment(const DevelopmentType d) {
    developments[static_cast<int>(d)] -= 1;
}

// Other Functions
const std::array<size_t, 10> DoganBank::getHand(void) const {
    std::array<size_t, 10> hand;
    std::copy(resources.begin(), resources.end(), hand.begin());
    std::copy(developments.begin(), developments.end(), hand.begin() + 5);
    return hand;
}