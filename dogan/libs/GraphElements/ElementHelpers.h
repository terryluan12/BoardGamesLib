#pragma once

#include "Coordinate.h"
#include "enums.h"

namespace Dogan {
std::array<std::pair<Direction, Direction>, 3>
getAllVertexRepresentations(Direction d);
std::array<std::pair<Direction, Direction>, 2>
getAllEdgeRepresentations(Direction d);
} // namespace Dogan