#pragma once

#include "Structure.h"
#include "Vertex.h"
#include "enums.h"
#include <set>
#include <utility>

namespace Dogan {
class Port {
public:
  Port(ResourceType r, std::set<Vertex> l) : resource(r), locations(l){};
  const ResourceType getResource(void) const { return resource; };
  const std::set<Vertex> getLocations(void) const { return locations; };
  friend std::ostream &operator<<(std::ostream &os, Port const &dp) {
    os << "Port: " << dp.getResource() << "\n";
    return os;
  };
  bool operator==(const Port &other) const {
    return this->locations == other.locations;
  }
  bool operator<(const Port &other) const {
    return this->locations < other.locations;
  }

private:
  ResourceType resource;
  std::set<Vertex> locations;
};
} // namespace Dogan