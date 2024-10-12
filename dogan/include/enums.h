#pragma once

#include <stdexcept>

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

enum class BuildingType {
    VILLAGE,
    CITY
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

Direction getOppositeDirection(Direction d);
std::pair<Direction, Direction> getComplementDirections(Direction d);