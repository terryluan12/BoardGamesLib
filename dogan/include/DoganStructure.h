#pragma once

#include "DoganEdge.h"
#include "DoganVertex.h"
#include <vector>

enum class BuildingType { VILLAGE = 0, CITY = 1, ROAD = 2 };

template <BuildingType T> class DoganBuilding {
public:
  DoganBuilding(int pid = -1) : playerID(pid) {
    if (T == BuildingType::ROAD) {
      throw std::invalid_argument("Error: Invalid Building Type");
    }
  };
  void addVertex(DoganVertex &dv);
  void setPlayerID(int pid);

private:
  int playerID;
  std::vector<DoganVertex> vertices;
};

class DoganRoad {
public:
  void addEdge(DoganEdge de, DoganCell &dc);
  void setPlayerID(int pid);

private:
  int playerID;
  std::vector<DoganEdge> edges;
};

#include "DoganStructure.tpp"