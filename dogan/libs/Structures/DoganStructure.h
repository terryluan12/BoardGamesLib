#pragma once

#include "DoganGraphElement.h"
#include <vector>

class DoganStructure {
  public:
    enum class StructureType { VILLAGE = 0, CITY = 1, ROAD = 2 };
    StructureType getStructureType(void);
    void setPlayerID(int pid);
    void setStructureType(StructureType t);
    static const std::size_t NUM_STRUCTURE_TYPES;
    std::vector<DoganGraphElement> getGraphElements(void);
    virtual ~DoganStructure(void){};
  protected:
    DoganStructure(int pid, StructureType t) : playerID(pid), type(t){};
    std::vector<DoganGraphElement> graphElements;
  private:
    int playerID;
    StructureType type;
  
};

using StructureType = DoganStructure::StructureType;
