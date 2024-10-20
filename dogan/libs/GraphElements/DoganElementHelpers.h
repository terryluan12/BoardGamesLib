#pragma once

#include "Coordinate.h"
#include "enums.h"

std::vector<std::pair<Coordinate2D, Direction>> getAllVertexRepresentations(std::pair<Coordinate2D, Direction> dvp);
std::vector<std::pair<Coordinate2D, Direction>> getAllEdgeRepresentations(std::pair<Coordinate2D, Direction> dep);