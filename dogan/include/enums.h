#pragma once

#include "common.h"
#include <ostream>

enum class ResourceType {
    WOOD = 0,
    SHEEP = 1,
    WHEAT = 2,
    BRICK = 3,
    STONE = 4,
    INVAL = 5
};
enum class DevelopmentType {
    VICPOINT = 0,
    MONOPOLY = 1,
    SOLDIER = 2,
    BUILDROAD = 3,
    TAKETWO = 4,
    INVAL = 5
};


enum class Parity {
    EVEN,
    ODD
};

enum class ResourceConfiguration {
    DEFAULT,
};

enum class NumberConfiguration {
    DEFAULT,
};

enum class Direction {
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST
};

inline std::array vertexDirections = {
        Direction::NORTH,
        Direction::NORTHEAST,
        Direction::SOUTHEAST,
        Direction::SOUTH,
        Direction::SOUTHWEST,
        Direction::NORTHWEST
    };

inline std::array edgeDirections = {
    Direction::NORTHEAST,
    Direction::EAST,
    Direction::SOUTHEAST,
    Direction::SOUTHWEST,
    Direction::WEST,
    Direction::NORTHWEST
};

Direction getOppositeDirection(Direction d);
std::pair<Direction, Direction> getComplementDirections(Direction d);
std::ostream &operator<< (std::ostream &os, Direction const &d);
std::ostream &operator<< (std::ostream &os, ResourceType const &d);
std::ostream &operator<< (std::ostream &os, DevelopmentType const &d);