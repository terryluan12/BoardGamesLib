#pragma once

#include "DoganStructureType.h"
#include <memory>
#include <vector>

class DoganStructure {
public:
  StructureType getStructureType(void) const;
  void setPlayerID(int pid);
  void setStructureType(StructureType t);
  int getPlayerID(void) const;
  virtual ~DoganStructure(void){};

protected:
  DoganStructure(StructureType t) : type(t){};
  int playerID;
  StructureType type;
};