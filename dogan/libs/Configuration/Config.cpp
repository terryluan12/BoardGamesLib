#include "Config.h"
#include "Vertex.h"
#include <algorithm>
#include <iostream>
#include <random>

namespace Dogan {
const std::vector<Coordinate2D> Config::getTileLocations(void) const {
  return tileLocations;
}
const std::vector<std::set<VertexPrimitive>>
Config::getPortLocations(void) const {
  return portLocations;
}
Coordinate2D Config::getRobberLocation(void) const {
  return robberLocation;
}

std::array<int, 3> Config::getTotalStructureCount(void) const {
  return totalStructureCount;
}
const std::array<size_t, 5> Config::getResourceCount(void) const {
  return resourceCount;
}
const std::array<size_t, 5> Config::getDevelopmentCount(void) const {
  return developmentCount;
}

std::vector<ResourceType> Config::getBoardResourceOrder() {
  return boardResourceOrder;
}
std::vector<ResourceType> Config::getPortResourceOrder() {
  return portResourceOrder;
}
std::vector<pip> Config::getNumberOrder() {
  return numberOrder;
}
std::vector<DevelopmentType> Config::getDevelopmentOrder() {
  return developmentOrder;
}

// Setters

void Config::setTileLocations(std::vector<Coordinate2D> tl) {
  tileLocations = tl;
}
void Config::setPortLocations(std::vector<std::set<VertexPrimitive>> pls) {
  portLocations = pls;
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
  portLocations = sets;
}
void Config::setRobberLocation(Coordinate2D irl) {
  robberLocation = irl;
}

void Config::setTotalStructureCount(std::array<int, 3> tsc) {
  totalStructureCount = tsc;
}
void Config::setResourceCount(std::array<size_t, 5> rc) {
  resourceCount = rc;
}
void Config::setDevelopmentCount(std::array<size_t, 5> dc) {
  developmentCount = dc;
}

void Config::setBoardResourceOrder(std::vector<ResourceType> r) { 
  boardResourceOrder = r; 
}
void Config::setPortResourceOrder(std::vector<ResourceType> pr) {
  portResourceOrder = pr;
}
void Config::setNumberOrder(std::vector<pip> nl) {
  numberOrder = nl;
}
void Config::setDevelopmentOrder(std::vector<DevelopmentType> dl) {
  developmentOrder = dl;
}

void Config::setBoardResourceConfig(Configuration brc) { 
  boardResourceConfig = brc; 
}
void Config::setPortResourceConfig(Configuration prc) {
  portResourceConfig = prc;
}
void Config::setNumberConfig(Configuration nc) { 
  numberConfig = nc; 
}
void Config::setDevelopmentConfig(Configuration dc) {
  developmentConfig = dc;
}
} // namespace Dogan