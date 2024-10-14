#include "DoganPlayer.h"


int DoganPlayer::getVictoryPoints(void) const {
    return victoryPoints;
}
void DoganPlayer::setVictoryPoints(const int vp) {
    victoryPoints = vp;
}
const std::vector<DoganCard> DoganPlayer::getHand(void) const {
    return hand;
}
std::string DoganPlayer::getName(void) const {
    return name;
};


std::ostream& operator<<(std::ostream& os, const DoganPlayer& p) {
    os << "Player " << p.getName() << ": \tVP: " << p.getVictoryPoints() << "\tHand: ";
    for(auto & c : p.getHand()) {
        os << c << " ";
    }
    os << "\n";
    return os;
}