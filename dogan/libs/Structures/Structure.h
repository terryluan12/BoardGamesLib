#pragma once

#include "Element.h"
#include "Node.h"
#include "enums.h"
#include <memory>
#include <vector>

namespace Dogan {

class Structure : public Node {
public:
  virtual ~Structure() = default;
  StructureType getStructureType(void) const;
  void setPlayerID(int pid);
  void setStructureType(StructureType t);
  const int getPlayerID(void) const;
  virtual const Element &getLocation(void) const = 0;

protected:
  Structure(StructureType t) : structureType(t){};
  Structure(StructureType t, int pid) : structureType(t), playerID(pid){};
  StructureType structureType;
  int playerID;
};
} // namespace Dogan