#pragma once

#include "DoganGraphElement.h"
#include "DoganStructureType.h"
#include <memory>
#include <vector>

class DoganStructure {
public:
  static const std::size_t NUM_STRUCTURE_TYPES;
  StructureType getStructureType(void);
  void setPlayerID(int pid);
  void setStructureType(StructureType t);
  std::vector<std::shared_ptr<DoganGraphElement>> getGraphElements(void);
  int getPlayerID(void);
  void setGraphElements(std::vector<std::shared_ptr<DoganGraphElement>> ge);
  virtual ~DoganStructure(void){};

protected:
  DoganStructure(StructureType t) : type(t){};
  std::vector<std::shared_ptr<DoganGraphElement>> graphElements;
  int playerID;
  StructureType type;
};