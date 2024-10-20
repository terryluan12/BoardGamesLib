#pragma once

#include "enums.h"
#include <array>
#include <cstddef>

class DoganBank {
public:
  DoganBank(void);
  DoganBank(std::array<int, 5> r, std::vector<DevelopmentType> d);
  friend std::ostream &operator<<(std::ostream &os, DoganBank const &d);

  // Resource Functions
  void addResource(const ResourceType r, const int n);
  void addResources(const std::array<int, 5> r);
  const std::array<int, 5> getResourceCount(void) const;
  void setResources(const std::array<int, 5> r);

  // Development Functions
  void addDevelopment(const DevelopmentType d);
  const std::array<int, 5> getDevelopmentCount(void) const;
  const std::vector<DevelopmentType> getDevelopments(void) const;
  void setDevelopments(const std::vector<DevelopmentType> d);
  DevelopmentType popDevelopment(void);

  // Other Functions
  bool canAfford(const std::array<int, 5> r) const;
  bool canAfford(ResourceType r, int n) const;

private:
  std::array<int, 5> resources;
  std::vector<DevelopmentType> developments;
  std::array<int, 5> developmentCount;
};
