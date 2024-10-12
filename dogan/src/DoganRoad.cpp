#include <functional>
#include <stdexcept>
#include <tuple>
#include "enums.h"
#include "DoganRoad.h"

void DoganRoad::addEdge(Edge &e, DoganCell &dc) {
    auto [d, c] = e;
    if(d == Direction::NORTH || d == Direction::SOUTH) {
        throw std::invalid_argument("Error: Direction::NORTH and Direction::SOUTH are invalid directions for edges");
    }
    edges.push_back(std::make_pair(e, dc));
    auto dc1 = dc.getAdjacentCell(d);
    if(dc1){
        Edge e1 = std::make_tuple(getOppositeDirection(d), dc1->getCoordinate());
        edges.push_back(std::make_pair(e1, *dc1));
    }
};

void DoganRoad::setPlayerID(int pid) {
    playerID = pid;
}