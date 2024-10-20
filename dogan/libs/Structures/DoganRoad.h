#pragma once

#include "DoganEdge.h"
#include "DoganExceptions.h"
#include "DoganStructure.h"
#include <vector>

class DoganRoad : public DoganStructure {
public:
  DoganRoad(int pid, DoganEdge de);

private:
  void addCorrespondingEdge(void);
};