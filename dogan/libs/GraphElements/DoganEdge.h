#pragma once

#include "Coordinate.h"
#include "DoganGraphElement.h"
#include "enums.h"
#include <vector>

class DoganEdge : public DoganGraphElement {
public:
  DoganEdge(Coordinate2D c, Direction d);
  DoganEdge getCorrespondingEdge(void);
};