#pragma once

enum class OrderConfiguration { DEFAULT, SHUFFLE, EXACT };

enum class ReplaceConfiguration { DEFAULT, REPLACE, EXACT };

using Configuration = std::tuple<OrderConfiguration, ReplaceConfiguration>;