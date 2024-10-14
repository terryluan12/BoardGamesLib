#pragma once

#include "enums.h"
#include <array>

class DoganPlayer {
    public:
        DoganPlayer(std::string n) : name(n), victoryPoints(0) {};

        // Victory Point Functions
        int getVictoryPoints(void) const;
        void setVictoryPoints(const int vp);

        // Resource Functions
        void addResource(const ResourceType r, const size_t n);
        const std::array<size_t, 5> getResources(void) const;
        size_t getResourceCount(const ResourceType r) const;
        void removeResource(const ResourceType r, const size_t n);
        void setResources(const std::array<size_t, 5> r);
        
        // Development Functions
        void addDevelopment(const DevelopmentType d);
        const std::array<size_t, 5> getDevelopments(void) const;
        size_t getDevelopmentCount(const DevelopmentType d) const;
        void removeDevelopment(const DevelopmentType d);
        void setDevelopments(const std::array<size_t, 5> d);

        // Other Functions
        const std::array<size_t, 10> getHand(void) const;
        std::string getName(void) const;
    private:
        std::string name;
        std::array<size_t, 5> resources;
        std::array<size_t, 5> developments;
        int victoryPoints;

};

std::ostream& operator<<(std::ostream& os, const DoganPlayer& p);