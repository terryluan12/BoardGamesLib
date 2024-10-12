#include "enums.h"

Direction getOppositeDirection(Direction d) {
    switch(d) {
        case(Direction::NORTH):
            return Direction::SOUTH;
        case(Direction::NORTHEAST):
            return Direction::SOUTHWEST;
        case(Direction::EAST):
            return Direction::WEST;
        case(Direction::SOUTHEAST):
            return Direction::NORTHWEST;
        case(Direction::SOUTH):
            return Direction::NORTH;
        case(Direction::SOUTHWEST):
            return Direction::NORTHEAST;
        case(Direction::WEST):
            return Direction::EAST;
        case(Direction::NORTHWEST):
            return Direction::SOUTHEAST;
        default:
            throw("Unexpected Error: Reached end of getOppositeDirection");
    }
}

std::pair<Direction, Direction> getComplementDirections(Direction d) {
    switch(d) {
        case(Direction::NORTH):
            return std::make_pair(Direction::SOUTHEAST, Direction::SOUTHWEST);
        case(Direction::NORTHEAST):
            return std::make_pair(Direction::SOUTH, Direction::NORTHWEST);
        case(Direction::SOUTHEAST):
            return std::make_pair(Direction::NORTH, Direction::SOUTHWEST);
        case(Direction::SOUTH):
            return std::make_pair(Direction::NORTHEAST, Direction::NORTHWEST);
        case(Direction::SOUTHWEST):
            return std::make_pair(Direction::NORTH, Direction::SOUTHEAST);
        case(Direction::NORTHWEST):
            return std::make_pair(Direction::SOUTH, Direction::NORTHEAST);
        default:
            throw std::invalid_argument("Error: Direction::EAST and Direction::WEST are invalid directions for edges");
    }
}