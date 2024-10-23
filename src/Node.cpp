#include "Node.h"
#include <vector>

std::unordered_set<std::shared_ptr<Node>> Node::getNthNeighbours(int level) {
  std::unordered_set<std::shared_ptr<Node>> levelNodes;
  std::vector<std::shared_ptr<Node>> currentLevelNodes;
  std::vector<std::shared_ptr<Node>> unexploredNodes{connectedNodes.begin(),
                                                     connectedNodes.end()};
  int currentLevel = level;

  if (level == 0) {
    return {};
  }

  while (level != 0) {
    currentLevelNodes = std::move(unexploredNodes);
    for (int i = 0; i < currentLevelNodes.size(); i++) {
      for (auto node : currentLevelNodes[i]->connectedNodes) {
        unexploredNodes.push_back(node);
      }
    }
    levelNodes.insert(currentLevelNodes.begin(), currentLevelNodes.end());

    currentLevelNodes.clear();
    level--;
  }
}