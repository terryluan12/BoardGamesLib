#pragma once

#include "DoganStructure.h"
#include "DoganVertex.h"
#include "enums.h"
#include <utility>

class DoganPort : public DoganStructure {
public:
  DoganPort(ResourceType r, std::vector<DoganVertex> v);
  const ResourceType getResource(void) const;
  friend std::ostream &operator<<(std::ostream &os, DoganPort const &dp);

private:
  ResourceType resource;
};