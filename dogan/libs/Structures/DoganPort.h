#pragma once

#include "DoganStructure.h"
#include "enums.h"
#include <utility>

class DoganPort : public DoganStructure {
public:
  DoganPort(ResourceType r)
      : DoganStructure(StructureType::PORT), resource(r){};
  const ResourceType getResource(void) const { return resource; };
  friend std::ostream &operator<<(std::ostream &os, DoganPort const &dp) {
    os << "Port " << dp.getResource() << ":\n";
    return os;
  };

private:
  ResourceType resource;
};