#pragma once

#include "Coordinate.h"
#include "DoganGraphElement.h"
#include "enums.h"

class DoganVertex : public DoganGraphElement {
public:
  DoganVertex(Coordinate2D c, Direction d);
  DoganVertex(Coordinate2D c, std::string d);
  std::vector<DoganVertex> getCorrespondingVertices(void);
};