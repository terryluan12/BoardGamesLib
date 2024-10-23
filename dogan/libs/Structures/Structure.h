#pragma once

#include "Node.h"
#include "enums.h"
#include <memory>
#include <vector>

namespace Dogan {
class Structure : public Node {
public:
  StructureType getStructureType(void) const;
  void setPlayerID(int pid);
  void setStructureType(StructureType t);
  int getPlayerID(void) const;
  virtual ~Structure(void){};

protected:
  Structure(StructureType t) : structureType(t){};
  int playerID;
  StructureType structureType;
};
} // namespace Dogan