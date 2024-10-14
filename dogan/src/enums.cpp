#include "enums.h"

std::ostream &operator<< (std::ostream &os, ResourceType const &rt) {
    switch(rt) {
        case ResourceType::STONE:
            os << "Stone";
            break;
        case ResourceType::WOOD:
            os << "Wood";
            break;
        case ResourceType::WHEAT:
            os << "Wheat";
            break;
        case ResourceType::SHEEP:
            os << "Sheep";
            break;
        case ResourceType::BRICK:
            os << "Brick";
            break;
        case ResourceType::OTHER:
            os << "Other";
            break;
    }
    return os;
}
std::ostream &operator<< (std::ostream &os, DevelopmentType const &dt) {
    switch(dt) {
        case DevelopmentType::VICPOINT:
            os << "Victory Point";
            break;
        case DevelopmentType::MONOPOLY:
            os << "Monopoly";
            break;
        case DevelopmentType::SOLDIER:
            os << "Soldier";
            break;
        case DevelopmentType::BUILDROAD:
            os << "Build Road";
            break;
        case DevelopmentType::TAKETWO:
            os << "Take Two";
            break;
    }
    return os;
}