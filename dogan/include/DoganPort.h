#pragma once

#include <utility>
#include "enums.h"
#include "DoganBuilding.h"
#include "DoganVertex.h"

class DoganPort {
    public:
        DoganPort(Resource r, std::pair<DoganVertex, DoganVertex> v) : resource(r), vertices(v) {};
    private:
        Resource resource;
        std::pair<DoganVertex, DoganVertex> vertices;
};