#pragma once

#include "Coordinate.h"
#include "DoganGraphElement.h"
#include "enums.h"
#include <vector>

class DoganEdge : public DoganGraphElement {
public:
  DoganEdge(Coordinate2D c, Direction d);
  DoganEdge(DoganEdge&& other) noexcept : DoganGraphElement(other.coordinates, other.direction) {}
  DoganEdge(const DoganEdge& other) noexcept : DoganGraphElement(other.coordinates, other.direction) {}
  DoganEdge& operator=(const DoganEdge& other) {
    if (this != &other) {
      coordinates = other.coordinates;
      direction = other.direction;
    }
    return *this;
  }
  std::vector<std::shared_ptr<DoganGraphElement>> getAllRepresentations(void) const override;
};