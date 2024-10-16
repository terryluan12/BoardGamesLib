#include "DoganPlayer.h"

// Victory Point Functions

int DoganPlayer::getVictoryPoints(void) const {
    return victoryPoints;
}
void DoganPlayer::setVictoryPoints(const int vp) {
    victoryPoints = vp;
}

DoganBank DoganPlayer::getInventory(void) const {
    return inventory;
}

std::string DoganPlayer::getName(void) const {
    return name;
};



std::ostream& operator<<(std::ostream& os, const DoganPlayer& p) {
    os << "Player " << p.getName() << ": \n  VP: " << p.getVictoryPoints() << "\n  Resource Cards:\n";
    for(size_t i = 0; i < 5; ++i) { 
        ResourceType rt = static_cast<ResourceType>(i);
        os << "    " << rt << ": " << p.getInventory().getResourceCount(rt) << "\n";
    }
    os << "  Development Cards:\n";
    for(size_t i = 0; i < 5; ++i) {
        DevelopmentType dt = static_cast<DevelopmentType>(i);
        os << "    " << dt << ": " << p.getInventory().getDevelopmentCount(dt) << "\n";
    }
    os << "\n";
    return os;
}