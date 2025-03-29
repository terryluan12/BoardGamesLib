#pragma once

#include <string>

namespace Dogan {
struct Response {
  bool succeeded;
  std::string message = "";
};
} // namespace Dogan