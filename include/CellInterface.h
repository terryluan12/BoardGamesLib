#pragma once

#include <memory>

class CellInterface {
    public:
        virtual ~CellInterface() = default;
        virtual std::string toString(void) const=0;
};