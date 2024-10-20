#include "DoganPort.h"

DoganPort::DoganPort(ResourceType r, std::vector<DoganVertex> v) : DoganStructure(StructureType::PORT), resource(r) {
}

const ResourceType DoganPort::getResource(void) const { return resource; }


std::ostream &operator<<(std::ostream &os, DoganPort const &dp) {
  os << "Port " << dp.getResource() << ":\n";

  return os;
}
