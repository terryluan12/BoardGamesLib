#include "HexagonalDirection.h"

using Direction = HexagonalDirection::Direction;

const Direction HexagonalDirection::fromString(std::string d) {
    if(d == "N") 
        return Direction::NORTH;
    else if(d == "NE")
        return Direction::NORTHEAST;
    else if(d == "E")
        return Direction::EAST;
    else if(d == "SE")
        return Direction::SOUTHEAST;
    else if(d == "S")
        return Direction::SOUTH;
    else if(d == "SW")
        return Direction::SOUTHWEST;
    else if(d == "W")
        return Direction::WEST;
    else if(d == "NW")
        return Direction::NORTHWEST;
    else
        throw std::invalid_argument("Error: Invalid Direction");
}

const Coordinate2D HexagonalDirection::toCoordinate(Direction d) {
    switch(d) {
        case Direction::NORTH:
            return {0, 1};
        case Direction::NORTHEAST:
            return {1, 1};
        case Direction::EAST:
            return {1, 0};
        case Direction::SOUTHEAST:
            return {1, -1};
        case Direction::SOUTH:
            return {0, -1};
        case Direction::SOUTHWEST:
            return {-1, -1};
        case Direction::WEST:
            return {-1, 0};
        case Direction::NORTHWEST:
            return {-1, 1};
    }
}

Direction HexagonalDirection::getOppositeDirection(Direction d) {
    switch(d) {
        case Direction::NORTH:
            return Direction::SOUTH;
        case Direction::NORTHEAST:
            return Direction::SOUTHWEST;
        case Direction::EAST:
            return Direction::WEST;
        case Direction::SOUTHEAST:
            return Direction::NORTHWEST;
        case Direction::SOUTH:
            return Direction::NORTH;
        case Direction::SOUTHWEST:
            return Direction::NORTHEAST;
        case Direction::WEST:
            return Direction::EAST;
        case Direction::NORTHWEST:
            return Direction::SOUTHEAST;
        default:
            throw("Unexpected Error: Reached end of getOppositeDirection");
    }
}

std::pair<Direction, Direction> HexagonalDirection::getComplementaryDirections(Direction d) {
    switch(d) {
        case Direction::NORTH:
            return std::make_pair(Direction::SOUTHEAST, Direction::SOUTHWEST);
        case Direction::NORTHEAST:
            return std::make_pair(Direction::SOUTH, Direction::NORTHWEST);
        case Direction::SOUTHEAST:
            return std::make_pair(Direction::NORTH, Direction::SOUTHWEST);
        case Direction::SOUTH:
            return std::make_pair(Direction::NORTHEAST, Direction::NORTHWEST);
        case Direction::SOUTHWEST:
            return std::make_pair(Direction::NORTH, Direction::SOUTHEAST);
        case Direction::NORTHWEST:
            return std::make_pair(Direction::SOUTH, Direction::NORTHEAST);
        default:
            throw std::invalid_argument("Error: Direction::EAST and Direction::WEST are invalid directions for edges");
    }
}

const std::array<Direction, 6> HexagonalDirection::getEdgeDirections(void) {
    return {
        Direction::NORTHEAST,
        Direction::EAST,
        Direction::SOUTHEAST,
        Direction::SOUTHWEST,
        Direction::WEST,
        Direction::NORTHWEST
    };
}

const std::array<Direction, 6> HexagonalDirection::getVertexDirections(void) {
    return {
        Direction::NORTH,
        Direction::NORTHEAST,
        Direction::SOUTHEAST,
        Direction::SOUTH,
        Direction::SOUTHWEST,
        Direction::NORTHWEST
    };
}

const std::array<Direction, 8> HexagonalDirection::getAllDirections(void) {
    return {
        Direction::NORTH,
        Direction::NORTHEAST,
        Direction::EAST,
        Direction::SOUTHEAST,
        Direction::SOUTH,
        Direction::SOUTHWEST,
        Direction::WEST,
        Direction::NORTHWEST
    };
}


std::ostream &operator<< (std::ostream &os, Direction const &d) {
  switch(d){
    case Direction::NORTH:
        os << "North";
        break;
    case Direction::NORTHEAST:
        os << "NorthEast";
        break;
    case Direction::EAST:
        os << "NorthEast";
        break;
    case Direction::SOUTHEAST:
        os << "SouthEast";
        break;
    case Direction::SOUTH:
        os << "South";
        break;
    case Direction::SOUTHWEST:
        os << "SouthWest";
        break;
    case Direction::WEST:
        os << "NorthWest";
        break;
    case Direction::NORTHWEST:
        os << "NorthWest";
        break;
  }

  return os;
}
