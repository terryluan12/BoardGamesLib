#include "Element.h"

bool Element::operator==(const Element &other) const {
  return this->coordinate == other.coordinate &&
         this->direction == other.direction;
}

bool Element::operator<(const Element &other) const {
  if (this->coordinate != other.coordinate) {
    return this->coordinate < other.coordinate;
  } else {
    return this->direction < other.direction;
  }
}