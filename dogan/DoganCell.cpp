#include <sstream>
#include <string>
#include "DoganCell.h"

std::string DoganCell::toString(void) {
    std::ostringstream oss;
    oss << "Type: " << static_cast<int>(type) << "; ContainsRobber: " << containsRobber << ", Number: " << number;
    return oss.str();

    // TODO: Change when g++ supports C++20
    // return std::format("Type: {}; ContainsRobber: {}, Number: {}", type, containsRobber, number);
};

void DoganCell::setRobber(bool robber) {
    this->containsRobber=robber;
}
