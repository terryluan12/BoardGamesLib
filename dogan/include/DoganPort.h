#pragma once

#include <utility>
#include "enums.h"
#include "DoganBuilding.h"

class DoganPort {
    public:
        DoganPort(Resource r, std::pair<Vertex, Vertex> v) : resource(r), vertices(v) {};
    private:
        Resource resource;
        std::pair<Vertex, Vertex> vertices;
};