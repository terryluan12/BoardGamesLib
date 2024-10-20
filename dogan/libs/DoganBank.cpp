#include "DoganBank.h"
#include "DoganExceptions.h"

DoganBank::DoganBank(void)
    : resources({0, 0, 0, 0, 0}), developments({}),
      developmentCount({0, 0, 0, 0, 0}) {}

DoganBank::DoganBank(std::array<int, 5> r, std::vector<DevelopmentType> d)
    : resources(r), developments(d), developmentCount({0, 0, 0, 0, 0}) {
  for (auto dev : d) {
    developmentCount[static_cast<int>(dev)] += 1;
  }
}

// Resource Functions
void DoganBank::addResource(const ResourceType r, const int n) {
  if (resources[static_cast<int>(r)] + n < 0) {
    throw InsufficientResourcesException("Error: Not enough resources");
  }
  resources[static_cast<int>(r)] += n;
}
void DoganBank::addResources(const std::array<int, 5> r) {
  for (size_t i = 0; i < 5; i++) {
    resources[i] += r[i];
  }
}
const std::array<int, 5> DoganBank::getResourceCount(void) const {
  return resources;
}
void DoganBank::setResources(const std::array<int, 5> r) { resources = r; }

// Development Functions
void DoganBank::addDevelopment(const DevelopmentType d) {
  developments.emplace_back(d);
  developmentCount[static_cast<int>(d)] += 1;
}

const std::array<int, 5> DoganBank::getDevelopmentCount(void) const {
  return developmentCount;
}

const std::vector<DevelopmentType> DoganBank::getDevelopments(void) const {
  return developments;
}

void DoganBank::setDevelopments(const std::vector<DevelopmentType> d) {
  for (auto dev : d) {
    developments.emplace_back(dev);
    developmentCount[static_cast<int>(dev)] += 1;
  }
}

DevelopmentType DoganBank::popDevelopment(void) {
  if (developments.empty()) {
    throw InsufficientDevelopmentsException("Error: No developments left");
  }
  DevelopmentType dt = developments.back();
  developments.pop_back();
  developmentCount[static_cast<int>(dt)] -= 1;
  return dt;
}

bool DoganBank::canAfford(const std::array<int, 5> r) const {
  for (size_t i = 0; i < 5; i++) {
    if (resources[i] < r[i]) {
      return false;
    }
  }
  return true;
}

bool DoganBank::canAfford(ResourceType r, int n) const {
  return resources[static_cast<int>(r)] > n;
}

std::ostream &operator<<(std::ostream &os, DoganBank const &d) {
  os << "Bank:\n"
     << "  Resource Cards:\n";

  for (size_t i = 0; i < 5; i++) {
    os << "    " << static_cast<ResourceType>(i) << ": "
       << d.getResourceCount()[i] << "\n";
  }
  os << "  Development Cards:\n";
  for (size_t i = 0; i < 5; i++) {
    os << "    " << static_cast<DevelopmentType>(i) << ": "
       << d.getDevelopmentCount()[i] << "\n";
  }
  os << "  Development Order:\n";
  for (auto dev : d.getDevelopments()) {
    os << "    " << dev << "\n";
  }
  return os;
}