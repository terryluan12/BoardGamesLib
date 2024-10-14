#pragma once

#include "Coordinate.h"
#include <array>
#include <map>
#include <utility>
#include <ostream>

// Direction
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

inline const std::array<Direction, 8> allDirections = {
    Direction::NORTH,
    Direction::NORTHEAST,
    Direction::EAST,
    Direction::SOUTHEAST,
    Direction::SOUTH,
    Direction::SOUTHWEST,
    Direction::WEST,
    Direction::NORTHWEST
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

inline const std::map<Direction, Coordinate2D> directionCoordinates = {
    {Direction::NORTH, {0, 1}},
    {Direction::NORTHEAST, {1, 1}},
    {Direction::EAST, {1, 0}},
    {Direction::SOUTHEAST, {1, -1}},
    {Direction::SOUTH, {0, -1}},
    {Direction::SOUTHWEST, {-1, -1}},
    {Direction::WEST, {-1, 0}},
    {Direction::NORTHWEST, {-1, 1}}
};

Direction getOppositeDirection(Direction d);


std::pair<Direction, Direction> getComplementDirections(Direction d);
std::ostream &operator<< (std::ostream &os, Direction const &d);