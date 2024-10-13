#pragma once

#include "enums.h"
#include "DoganVertex.h"
#include <utility>

class DoganPort {
    public:
        DoganPort(Resource r, std::pair<DoganVertex, DoganVertex> v) : resource(r), vertices(v) {};
    private:
        Resource resource;
        std::pair<DoganVertex, DoganVertex> vertices;
};