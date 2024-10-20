#include "DoganCell.h"

DoganCell::DoganCell(bool cr, Coordinate2D c, int n, ResourceType t)
    : coordinate(c), type(t) {}

Coordinate2D DoganCell::getCoordinate(void) const { return coordinate; }

ResourceType DoganCell::getResource(void) const { return this->type; }

std::ostream &operator<<(std::ostream &os, DoganCell const &dc) {
  os << "DoganCell " << dc.getCoordinate() << ": " << dc.getResource() << "\n";
  return os;
}