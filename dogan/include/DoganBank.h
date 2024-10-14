#pragma once

#include "enums.h"
#include <array>
#include <cstddef>

class DoganBank {
    public:
        DoganBank(void) : resources({0, 0, 0, 0, 0}){};
        DoganBank(std::array<size_t, 5> r, std::array<size_t, 5> d) : resources(r), developments(d){};

        // Resource Functions
        void addResource(const ResourceType r, const int n);
        size_t getResourceCount(const ResourceType r) const;
        const std::array<size_t, 5> getResources(void) const;
        void setResources(const std::array<size_t, 5> r);
        void removeResource(const ResourceType r, const int n);

        // Development Functions
        void addDevelopment(const DevelopmentType d);
        size_t getDevelopmentCount(const DevelopmentType d) const;
        const std::array<size_t, 5> getDevelopments(void) const;
        void setDevelopments(const std::array<size_t, 5> d);
        void removeDevelopment(const DevelopmentType d);

        // Other Functions
        const std::array<size_t, 10> getHand(void) const;
    private:
        std::array<size_t, 5> resources;
        std::array<size_t, 5> developments;
};