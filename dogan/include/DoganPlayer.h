#pragma once

#include "DoganCard.h"
#include <vector>

class DoganPlayer {
    public:
        DoganPlayer(std::string n) : name(n), victoryPoints(0) {};
        int getVictoryPoints(void) const;
        void setVictoryPoints(const int vp);
        const std::vector<DoganCard> getHand(void) const;
        std::string getName(void) const;
    private:
        std::string name;
        std::vector<DoganCard> hand;
        int victoryPoints;

};

std::ostream& operator<<(std::ostream& os, const DoganPlayer& p);