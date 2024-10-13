#pragma once

#include "common.h"

enum class Resource {
    WOOD,
    SHEEP,
    WHEAT,
    BRICK,
    STONE,
    INVAL
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