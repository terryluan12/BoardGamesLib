#include "DoganConfigBuilder.h"

DoganConfigBuilder& DoganConfigBuilder::setBoardSize(size_t s) {
    config.setBoardSize(s);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setParity(Parity p) {
    config.setParity(p);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setRobberLocation(Coordinate2D irl) {
    config.setRobberLocation(irl);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setTotalStructureCount(std::array<size_t, 3> tsc) {
    config.setTotalStructureCount(tsc);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setTileLocations(const std::vector<Coordinate2D>& tl) {
    config.setTileLocations(tl);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setResourceCount(std::array<size_t, 5> rc) {
    config.setResourceCount(rc);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setDevelopmentCount(std::array<size_t, 5> dc) {
    config.setDevelopmentCount(dc);
    return *this;
}

DoganConfigBuilder& DoganConfigBuilder::setDevelopmentConfig(OrderConfiguration dc) {
    config.setDevelopmentConfig(dc);
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

DoganConfigBuilder& DoganConfigBuilder::setDevelopmentLocations(const std::vector<DevelopmentType>& dl) {
    config.setDevelopmentLocations(dl);
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