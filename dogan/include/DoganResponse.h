#pragma once

#include <string>
#include <vector>

namespace Dogan {
struct Response {
  bool succeeded;
  std::string message = "";
  std::vector<int> result;
};
} // namespace Dogan