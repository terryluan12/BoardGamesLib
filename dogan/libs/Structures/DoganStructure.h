#pragma once

#include "DoganGraphElement.h"
#include <vector>
#include <memory>

class DoganStructure {
  public:
    enum class StructureType { VILLAGE = 0, CITY = 1, ROAD = 2 };
    static const std::size_t NUM_STRUCTURE_TYPES;
    StructureType getStructureType(void);
    void setPlayerID(int pid);
    void setStructureType(StructureType t);
    std::vector<std::shared_ptr<DoganGraphElement>> getGraphElements(void);
    void setGraphElements(std::vector<std::shared_ptr<DoganGraphElement>> ge);
    virtual ~DoganStructure(void){};
  protected:
    DoganStructure(int pid, StructureType t) : playerID(pid), type(t){};
    std::vector<std::shared_ptr<DoganGraphElement>> graphElements;
    int playerID;
    StructureType type;
  
};

using StructureType = DoganStructure::StructureType;
