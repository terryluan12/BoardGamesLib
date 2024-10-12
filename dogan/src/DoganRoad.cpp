#include <functional>
#include <stdexcept>
#include <tuple>
#include "enums.h"
#include "DoganRoad.h"

void DoganRoad::addEdge(Edge e) {
    auto [d, dc] = e;
    if(d == Direction::NORTH || d == Direction::SOUTH) {
        throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH are invalid directions for edges");
    }
    edges.push_back(e);
    Edge e1 = std::make_tuple(getOppositeDirection(d), dc->getAdjacentCell(d));
    edges.push_back(e1);
};

void DoganRoad::setPlayerID(int pid) {
    playerID = pid;
}