#pragma once

#include "Coordinate.h"
#include "DoganGraphElement.h"
#include "enums.h"

class DoganVertex : public DoganGraphElement {
public:
  DoganVertex(Coordinate2D c, Direction d);
  DoganVertex(DoganVertex&& other) noexcept : DoganGraphElement(other.coordinates, other.direction) {}
  DoganVertex(const DoganVertex& other) noexcept : DoganGraphElement(other.coordinates, other.direction) {}
  DoganVertex& operator=(const DoganVertex& other) {
    if (this != &other) {
      coordinates = other.coordinates;
      direction = other.direction;
    }
    return *this;
  }
  std::vector<std::shared_ptr<DoganGraphElement>> getAllRepresentations(void) const override;
};