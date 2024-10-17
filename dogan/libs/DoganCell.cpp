#include "DoganCell.h"
#include <sstream>

std::unordered_set<Coordinate2D> DoganCell::allCoordinates;

DoganCell::DoganCell(bool cr, Coordinate2D c, int n, ResourceType t)
    : containsRobber(cr), coordinate(c), number(n), type(t) {
  auto [_, didInsert] = allCoordinates.insert(c);
  if (!didInsert) {
    throw std::invalid_argument("Error: Cell already exists");
  }
}

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