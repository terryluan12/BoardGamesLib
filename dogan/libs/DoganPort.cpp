#include "DoganPort.h"

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
