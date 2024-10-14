#include "DoganPlayer.h"

// Victory Point Functions

int DoganPlayer::getVictoryPoints(void) const {
    return victoryPoints;
}
void DoganPlayer::setVictoryPoints(const int vp) {
    victoryPoints = vp;
}

// Resource Functions
void DoganPlayer::addResource(const ResourceType r, const size_t n) {
    resources[static_cast<int>(r)] += n;
}
const std::array<size_t, 5> DoganPlayer::getResources(void) const {
    return resources;
}
size_t DoganPlayer::getResourceCount(const ResourceType r) const {
    return resources[static_cast<int>(r)];
}
void DoganPlayer::setResources(const std::array<size_t, 5> r) {
    resources = r;
}
void DoganPlayer::removeResource(const ResourceType r, const size_t n) {
    resources[static_cast<int>(r)] -= n;
}

// Development Functions
void DoganPlayer::addDevelopment(const DevelopmentType d) {
    developments[static_cast<int>(d)] += 1;
}
const std::array<size_t, 5> DoganPlayer::getDevelopments(void) const {
    return developments;
}
size_t DoganPlayer::getDevelopmentCount(const DevelopmentType d) const {
    return developments[static_cast<int>(d)];
};
void DoganPlayer::removeDevelopment(const DevelopmentType d) {
    developments[static_cast<int>(d)] -= 1;
}
void DoganPlayer::setDevelopments(const std::array<size_t, 5> d) {
    developments = d;
}

// Other Functions
const std::array<size_t, 10> DoganPlayer::getHand(void) const {
    std::array<size_t, 10> hand;
    std::copy(resources.begin(), resources.end(), hand.begin());
    std::copy(developments.begin(), developments.end(), hand.begin() + 5);
    return hand;
}
std::string DoganPlayer::getName(void) const {
    return name;
};



std::ostream& operator<<(std::ostream& os, const DoganPlayer& p) {
    os << "Player " << p.getName() << ": \n  VP: " << p.getVictoryPoints() << "\n  Resources:\n";
    for(size_t i = 0; i < 5; ++i) { 
        os << "\t" << static_cast<ResourceType>(i) << ": " << p.getResources()[i] << "\n";
    }
    os << "  Developments:\n";
    for(size_t i = 0; i < 5; ++i) {
        os << "\t" << static_cast<DevelopmentType>(i) << ": " << p.getDevelopments()[i] << "\n";
    }
    os << "\n";
    return os;
}