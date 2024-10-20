#include "Cell.h"

namespace Dogan {
Cell::Cell(bool cr, Coordinate2D c, int n, ResourceType t)
    : coordinate(c), type(t) {}

Coordinate2D Cell::getCoordinate(void) const { return coordinate; }

ResourceType Cell::getResource(void) const { return this->type; }

std::ostream &operator<<(std::ostream &os, Cell const &dc) {
  os << "Cell " << dc.getCoordinate() << ": " << dc.getResource() << "\n";
  return os;
}
} // namespace Dogan