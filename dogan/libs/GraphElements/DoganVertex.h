#pragma once

#include "Coordinate.h"
#include "DoganGraphElement.h"
#include "enums.h"

class DoganVertex : public DoganGraphElement {
public:
  DoganVertex(Coordinate2D c, Direction d);
  std::vector<DoganVertex> getCorrespondingVertices(void);
};