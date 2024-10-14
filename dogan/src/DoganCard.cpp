#include "DoganCard.h"

std::ostream &operator<< (std::ostream &os, DoganCard const &d) {
    if(d.isResourceCard()) {
        os << std::get<ResourceType>(d.getCard());
    } else {
        os << std::get<DevelopmentType>(d.getCard());
    }
    return os;
}

std::variant<ResourceType, DevelopmentType> DoganCard::getCard(void) const {
    return card;
}