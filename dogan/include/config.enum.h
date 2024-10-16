
enum class OrderConfiguration {
    DEFAULT,
    SHUFFLE,
    EXACT
};

enum class ReplaceConfiguration {
    DEFAULT,
    REPLACE,
    EXACT
};

enum class Parity {
    EVEN,
    ODD
};

using Configuration = std::tuple<OrderConfiguration, ReplaceConfiguration>;