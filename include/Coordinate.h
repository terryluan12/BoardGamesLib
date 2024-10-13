#pragma once

#include <cstdlib>
#include <stdexcept>
#include <functional>
#include <utility>
#include <initializer_list>

template<size_t N>
class Coordinate {
    public:
        static_assert(N > 0, "Error: N must be greater than 0");
        Coordinate(int x=0, int y=0) : coordinates({x, y}) {};
        Coordinate(std::array<int, N> c) : coordinates(c) {};
        Coordinate(std::initializer_list<int> parameters);

        int operator[](const size_t ci) const;
        inline bool operator==(const Coordinate& c) const {return coordinates == c.coordinates;};
        bool operator<(const Coordinate &c) const;
        Coordinate<N> operator+(Coordinate const& obj) const;
        Coordinate<N> operator-(Coordinate const& obj) const;

        int getX(void) const;
        int getY(void) const;

        template<size_t M>
        decltype(auto) get(void) const;
    private:
        static const size_t coordSize=N;
        std::array<int, N> coordinates;
};

#include "../src/Coordinate.tpp"
