#pragma once

#include "Coordinate.h"
#include <array>
#include <map>
#include <utility>
#include <ostream>

class HexagonalDirection {
    public:
    // Direction
    enum class Direction {
        SOUTH,
        NORTHEAST,
        EAST,
        SOUTHEAST,
        NORTH,
        SOUTHWEST,
        WEST,
        NORTHWEST
    };
    
    // static methods
    static const Direction fromString(std::string d);
    static const Coordinate2D toCoordinate(Direction d);

    static Direction getOppositeDirection(Direction d);
    static std::pair<Direction, Direction> getComplementaryDirections(Direction d);

    static const std::array<Direction, 6> getEdgeDirections(void);
    static const std::array<Direction, 6> getVertexDirections(void);
    static const std::array<Direction, 8> getAllDirections(void);

};


std::ostream &operator<< (std::ostream &os, HexagonalDirection::Direction const &d);