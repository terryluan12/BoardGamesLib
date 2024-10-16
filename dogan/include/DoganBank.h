#pragma once

#include "enums.h"
#include <array>
#include <cstddef>

class DoganBank {
public:
  DoganBank(void);
  DoganBank(std::array<size_t, 5> r, std::vector<DevelopmentType> d);

  // Resource Functions
  void addResource(const ResourceType r, const int n);
  void addResources(const std::array<size_t, 5> r);
  size_t getResourceCount(const ResourceType r) const;
  const std::array<size_t, 5> getTotalResources(void) const;
  void setResources(const std::array<size_t, 5> r);
  void removeResource(const ResourceType r, const int n);
  void removeResources(const std::array<size_t, 5> r);
  bool canAfford(const std::array<size_t, 5> r);

  // Development Functions
  void addDevelopment(const DevelopmentType d);
  size_t getDevelopmentCount(const DevelopmentType d) const;
  const std::array<size_t, 5> getTotalDevelopments(void) const;
  void setDevelopments(const std::vector<DevelopmentType> d);
  DevelopmentType popDevelopment(void);

  // Other Functions
  const std::array<size_t, 10> getFullCount(void) const;

private:
  std::array<size_t, 5> resources;
  std::vector<DevelopmentType> developments;
  std::array<size_t, 5> developmentCount;
};

std::ostream &operator<<(std::ostream &os, DoganBank const &d);