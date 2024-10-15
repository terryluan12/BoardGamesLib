#include "DoganConfigBuilder.h"

DoganConfigBuilder& DoganConfigBuilder::setBoardSize(size_t s) {
    config.boardSize = s;
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setParity(Parity p) {
    config.parity = p;
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setRobberPosition(Coordinate2D irl) {
    config.initialRobberLocation = irl;
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setTileLocations(const std::vector<Coordinate2D>& tl) {
    config.initialTileLocations = tl;
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setResourceCount(std::array<size_t, 5> rc) {
    config.initialResourceCount = rc;
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setDevelopmentCount(std::array<size_t, 5> dc) {
    config.initialDevelopmentCount = dc;
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setNumberConfig(OrderConfiguration nc) {
    config.setNumberConfig(nc);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setPortResourceConfig(OrderConfiguration prc) {
    config.setPortResourceConfig(prc);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setResourceConfig(OrderConfiguration rc) {
    config.setResourceConfig(rc);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setNumberLocations(const std::vector<int>& nl) {
    config.setNumberLocations(nl);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setPortLocations(const std::vector<std::vector<DoganVertex>>& pl) {
    config.setPortLocations(pl);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setResources(const std::vector<ResourceType>& r) {
    config.setResources(r);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setPortResources(const std::vector<ResourceType>& pr) {
    config.setPortResources(pr);
    return *this;
}

DoganConfig DoganConfigBuilder::build() {
    return config;
}