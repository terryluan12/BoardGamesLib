#pragma once

#include "DoganConfig.h"
#include <vector>
#include <array>

class DoganConfigBuilder {
public:
    DoganConfigBuilder& setBoardSize(size_t s);
    DoganConfigBuilder& setParity(Parity p);
    DoganConfigBuilder& setRobberPosition(Coordinate2D irl);
    DoganConfigBuilder& setTileLocations(const std::vector<Coordinate2D>& tl);
    DoganConfigBuilder& setResourceCount(std::array<size_t, 5> rc);
    DoganConfigBuilder& setDevelopmentCount(std::array<size_t, 5> dc);
    DoganConfigBuilder& setNumberConfig(OrderConfiguration nc);
    DoganConfigBuilder& setPortResourceConfig(OrderConfiguration prc);
    DoganConfigBuilder& setResourceConfig(OrderConfiguration rc);
    DoganConfigBuilder& setNumberLocations(const std::vector<int>& nl);
    DoganConfigBuilder& setPortLocations(const std::vector<std::vector<DoganVertex>>& pl);
    DoganConfigBuilder& setResources(const std::vector<ResourceType>& r);
    DoganConfigBuilder& setPortResources(const std::vector<ResourceType>& pr);
    DoganConfig build();

private:
    DoganConfig config;
};