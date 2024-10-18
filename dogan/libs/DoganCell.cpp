#include "DoganCell.h"
#include <sstream>

DoganCell::DoganCell(bool cr, Coordinate2D c, int n, ResourceType t)
    : containsRobber(cr), coordinate(c), number(n), type(t) {}

Coordinate2D DoganCell::getCoordinate(void) const { return coordinate; }

int DoganCell::getNumber(void) const { return this->number; }

ResourceType DoganCell::getResource(void) const { return this->type; }

bool DoganCell::hasRobber(void) const { return this->containsRobber; }

void DoganCell::setRobber(bool robber) { this->containsRobber = robber; }

std::ostream &operator<<(std::ostream &os, DoganCell const &dc) {
  os << "DoganCell " << dc.getCoordinate() << ": Number(" << dc.getNumber()
     << "), Resource(" << dc.getResource() << "), hasRobber(" << dc.hasRobber()
     << ")"
     << "\n";
  return os;
}