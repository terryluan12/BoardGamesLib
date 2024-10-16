#pragma once

#include "enums.h"
#include "DoganBank.h"
#include <array>

class DoganPlayer {
    public:
        DoganPlayer(std::string n) : name(n), victoryPoints(0) {};

        int getVictoryPoints(void) const;
        void setVictoryPoints(const int vp);

        DoganBank getInventory(void) const;

        // Other Functions
        const std::array<size_t, 10> getFullCount(void) const;
        std::string getName(void) const;
    private:
        std::string name;
        DoganBank inventory;
        std::array<size_t, 5> resources;
        std::array<size_t, 5> developments;
        int victoryPoints;

};

std::ostream& operator<<(std::ostream& os, const DoganPlayer& p);