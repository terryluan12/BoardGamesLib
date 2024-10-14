#pragma once

#include "enums.h"
#include "DoganVertex.h"
#include <utility>

class DoganPort {
    public:
        DoganPort(ResourceType r, std::pair<DoganVertex, DoganVertex> v) : resource(r), vertices(v) {};
    private:
        ResourceType resource;
        std::pair<DoganVertex, DoganVertex> vertices;
};