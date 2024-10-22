#pragma once

#include <memory>
#include <unordered_set>

class Node {
    public:
        std::unordered_set<std::shared_ptr<Node>> getNthNeighbours(int level);
    protected:
        std::unordered_set<std::shared_ptr<Node>> connectedNodes;
};