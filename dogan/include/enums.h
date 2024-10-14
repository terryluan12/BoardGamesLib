#pragma once

#include "common.h"
#include <ostream>

enum class ResourceType {
    WOOD = 0,
    SHEEP = 1,
    WHEAT = 2,
    BRICK = 3,
    STONE = 4,
    OTHER = 5
};
enum class DevelopmentType {
    VICPOINT = 0,
    MONOPOLY = 1,
    SOLDIER = 2,
    BUILDROAD = 3,
    TAKETWO = 4,
};


enum class Parity {
    EVEN,
    ODD
};

std::ostream &operator<< (std::ostream &os, ResourceType const &d);
std::ostream &operator<< (std::ostream &os, DevelopmentType const &d);