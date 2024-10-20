#pragma once

namespace Dogan {
enum class OrderConfiguration { DEFAULT = 0, SHUFFLE = 1, EXACT = 2 };

enum class ReplaceConfiguration { DEFAULT = 0, REPLACE = 1, EXACT = 2 };

using Configuration = std::tuple<OrderConfiguration, ReplaceConfiguration>;
} // namespace Dogan