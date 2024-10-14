#pragma once

#include "enums.h"
#include <variant>

class DoganCard {
    public:
        DoganCard(std::variant<ResourceType, DevelopmentType> c) : card(c) {
            isResource = std::holds_alternative<ResourceType>(c);
        };
        bool isResourceCard(void) const { return isResource; };
        bool isDevelopmentCard(void) const { return !isResource; };
        std::variant<ResourceType, DevelopmentType> getCard(void) const ;
    private:
        std::variant<ResourceType, DevelopmentType> card;
        bool isResource;
};

std::ostream &operator<< (std::ostream &os, DoganCard const &d);
