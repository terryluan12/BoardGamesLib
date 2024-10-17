#include "DoganBank.h"
#include <iostream>

DoganBank::DoganBank(void)
    : resources({0, 0, 0, 0, 0}), developments({}),
      developmentCount({0, 0, 0, 0, 0}) {}

DoganBank::DoganBank(std::array<size_t, 5> r, std::vector<DevelopmentType> d)
    : resources(r), developments(d), developmentCount({0, 0, 0, 0, 0}) {
  for (auto dev : d) {
    developmentCount[static_cast<int>(dev)] += 1;
  }
}

// Resource Functions
void DoganBank::addResource(const ResourceType r, const int n) {
  resources[static_cast<int>(r)] += n;
}
void DoganBank::addResources(const std::array<size_t, 5> r) {
  for (size_t i = 0; i < 5; i++) {
    resources[i] += r[i];
  }
}
const std::array<size_t, 5> DoganBank::getResourceCount(void) const {
  return resources;
}
void DoganBank::setResources(const std::array<size_t, 5> r) { resources = r; }
void DoganBank::removeResource(const ResourceType r, const int n) {
  if (resources[static_cast<int>(r)] < n) {
    throw std::invalid_argument("Not enough resources to remove");
  }
  resources[static_cast<int>(r)] -= n;
}
void DoganBank::removeResources(const std::array<size_t, 5> r) {
  for (size_t i = 0; i < 5; i++) {
    resources[i] -= r[i];
  }
}

bool DoganBank::canAfford(const std::array<size_t, 5> r) {
  for (size_t i = 0; i < 5; i++) {
    if (resources[i] < r[i]) {
      return false;
    }
  }
  return true;
}

// Development Functions
void DoganBank::addDevelopment(const DevelopmentType d) {
  developments.push_back(d);
  developmentCount[static_cast<int>(d)] += 1;
}

const std::array<size_t, 5> DoganBank::getDevelopmentCount(void) const {
  return developmentCount;
}

const std::vector<DevelopmentType> DoganBank::getDevelopments(void) const {
  return developments;
}

void DoganBank::setDevelopments(const std::vector<DevelopmentType> d) {
  for (auto dev : d) {
    developments.push_back(dev);
    developmentCount[static_cast<int>(dev)] += 1;
  }
}
DevelopmentType DoganBank::popDevelopment(void) {
  if(developments.empty()) {
    throw std::invalid_argument("No developments to pop");
  }
  DevelopmentType dt = developments.back();
  developments.pop_back();
  developmentCount[static_cast<int>(dt)] -= 1;
  return dt;
}

std::ostream &operator<<(std::ostream &os, DoganBank const &d) {
  os << "Bank:\n"
     << "  Resource Cards:\n";
  
  for (auto &resource : d.getResourceCount()) {
    os << "    " << resource << ": " << d.getResourceCount()[resource] << "\n";
  }
  os << "  Development Cards:\n";
    for(size_t i = 0; i < 5; i++) {
      os << "    " << static_cast<DevelopmentType>(i) << ": " << d.getDevelopmentCount()[i] << "\n";
    }
  os << "  Development Order:\n";
  for(auto dev : d.getDevelopments()) {
    os << "    " << dev << "\n";
  }
  return os;
}