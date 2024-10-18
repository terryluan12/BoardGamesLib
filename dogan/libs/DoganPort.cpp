#include "DoganPort.h"

DoganPort::DoganPort(ResourceType r, std::vector<DoganVertex> v) : resource(r) {
  for(auto dv : v) {
    std::vector<DoganVertex> allRepresentations{};
    allRepresentations.push_back(dv);
    auto corrVertices = dv.getCorrespondingVertices();
    allRepresentations.insert(allRepresentations.end(), corrVertices.begin(), corrVertices.end());
    vertices.push_back(v);
  }
}

const ResourceType DoganPort::getResource(void) const { return resource; }

const std::vector<std::vector<DoganVertex>> DoganPort::getVertices(void) const {
  return vertices;
}

// std::ostream &operator<<(std::ostream &os, DoganPort const &dp) {
//   auto &vertices = dp.getVertices();
//   os << "Port " << dp.getResource() << ":\n";

//   for (size_t i = 0; i < vertices.size(); i++) {
//     os << "  [";

//     const auto &vec = vertices[i];
//     for (size_t j = 0; j < vec.size(); j++) {
//       os << vec[j];
//       if (j < vec.size() - 1) {
//         os << ", ";
//       }
//     }
//     os << "]\n";
//   }

//   return os;
// }
