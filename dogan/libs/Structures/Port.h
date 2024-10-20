#pragma once

#include "Structure.h"
#include "enums.h"
#include <utility>

namespace Dogan {
class Port : public Structure {
public:
  Port(ResourceType r) : Structure(StructureType::PORT), resource(r){};
  const ResourceType getResource(void) const { return resource; };
  friend std::ostream &operator<<(std::ostream &os, Port const &dp) {
    os << "Port " << dp.getResource() << ":\n";
    return os;
  };

private:
  ResourceType resource;
};
} // namespace Dogan