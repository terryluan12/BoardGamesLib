#pragma once

#include "DoganVertex.h"
#include "enums.h"
#include <utility>

class DoganPort {
public:
  DoganPort(ResourceType r, std::vector<std::vector<DoganVertex>> v)
      : resource(r), vertices(v){};
  friend std::ostream &operator<<(std::ostream &os, DoganPort const &dp);
  const std::vector<std::vector<DoganVertex>> getVertices(void) const;
  const ResourceType getResource(void) const;

private:
  ResourceType resource;
  std::vector<std::vector<DoganVertex>> vertices;
};