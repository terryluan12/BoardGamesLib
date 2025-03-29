#include "Config.h"
#include "Vertex.h"
#include <algorithm>
#include <iostream>
#include <random>

namespace Dogan {
std::vector<pip> Config::getNumbers() {
  return initialNumberLocations;
}

std::vector<ResourceType> Config::getPortResources() {
  return initialPortResources;
}

std::vector<ResourceType> Config::getResources() {
  return initialResources;
}

std::vector<DevelopmentType> Config::getDevelopments() {
  return initialDevelopmentLocations;
}

std::vector<std::set<VertexPrimitive>> Config::getPortLocations() {
  return initialPortLocations;
}

// Getters

std::array<int, 3> Config::getTotalStructureCount(void) const {
  return totalStructureCount;
}

Coordinate2D Config::getRobberLocation(void) const {
  return initialRobberLocation;
}

const std::vector<Coordinate2D> Config::getTileLocations(void) const {
  return initialTileLocations;
}

const std::vector<std::set<VertexPrimitive>>
Config::getPortLocations(void) const {
  return initialPortLocations;
}

const std::array<size_t, 5> Config::getResourceCount(void) const {
  return initialResourceCount;
}
const std::array<size_t, 5> Config::getDevelopmentCount(void) const {
  return initialDevelopmentCount;
}

// Setters

void Config::setTotalStructureCount(std::array<int, 3> tsc) {
  totalStructureCount = tsc;
}

void Config::setResourceCount(std::array<size_t, 5> rc) {
  initialResourceCount = rc;
}

void Config::setDevelopmentCount(std::array<size_t, 5> dc) {
  initialDevelopmentCount = dc;
}

void Config::setDevelopmentConfig(Configuration dc) {
  initialDevelopmentConfig = dc;
}

void Config::setNumberConfig(Configuration nc) { initialNumberConfig = nc; }

void Config::setPortResourceConfig(Configuration prc) {
  initialPortResourceConfig = prc;
}

void Config::setResourceConfig(Configuration rc) { initialResourceConfig = rc; }

void Config::setDevelopmentLocations(std::vector<DevelopmentType> dl) {
  initialDevelopmentLocations = dl;
}

void Config::setNumberLocations(std::vector<pip> nl) {
  initialNumberLocations = nl;
}

void Config::setPortLocations(std::vector<std::set<VertexPrimitive>> pls) {
  initialPortLocations = pls;
}

void Config::setPortLocations(std::vector<std::vector<VertexPrimitive>> pls) {
  std::vector<std::set<VertexPrimitive>> sets;

  for (const auto &v : pls) {
    auto set = std::set(v.begin(), v.end());
    if (set.size() != pls.size()) {
      std::cerr << "WARNING: Duplicate Port locations. please check your "
                   "configuration or data for errors."
                << std::endl;
    }
    sets.push_back(set);
  }
  initialPortLocations = sets;
}

void Config::setRobberLocation(Coordinate2D irl) {
  initialRobberLocation = irl;
}

void Config::setTileLocations(std::vector<Coordinate2D> tl) {
  initialTileLocations = tl;
}

void Config::setResources(std::vector<ResourceType> r) { initialResources = r; }

void Config::setPortResources(std::vector<ResourceType> pr) {
  initialPortResources = pr;
}
} // namespace Dogan