#include "Coordinate.h"
#include <memory>
#include <ostream>
#include <stdexcept>

template <size_t N> class Coordinate;

namespace std {
template <size_t N>
struct tuple_size<Coordinate<N>> : integral_constant<size_t, N> {};

template <size_t N, size_t M> struct tuple_element<M, Coordinate<N>> {
  static_assert(M < N, "Index out of bounds");
  using type = int;
};

template <size_t N> struct hash<Coordinate<N>> {
  size_t operator()(const Coordinate<N> &coord) const {
    for (size_t i = 0; i < N; i++) {
      std::hash<int>()(coord[i]);
    }
    return std::hash<int>()(coord.getX()) ^ std::hash<int>()(coord.getY());
  }
};
}; // namespace std

template <size_t N>
Coordinate<N>::Coordinate(std::initializer_list<int> parameters) {
  if (parameters.size() != N) {
    throw std::out_of_range("Error: initializer list size must be " + N);
  }
  std::copy(parameters.begin(), parameters.end(), coordinates.begin());
}

template <size_t N> int Coordinate<N>::operator[](const size_t ci) const {
  if (ci < N) {
    return coordinates[ci];
  }
  throw std::out_of_range("Error: attempting to access Coordinate of size" +
                          std::to_string(coordSize) + " with index " +
                          std::to_string(ci));
}

template <size_t N> bool Coordinate<N>::operator==(const Coordinate &c) const {
  for (size_t i = 0; i < N; i++) {
    if (c.coordinates[i] != this->coordinates[i]) {
      return false;
    }
  }
  return true;
}

template <size_t N>
bool Coordinate<N>::operator<(const Coordinate<N> &c) const {
  for (size_t i = 0; i < N; i++) {
    if (this->coordinates[i] < c.coordinates[i])
      return true;
    if (this->coordinates[i] > c.coordinates[i])
      return false;
  }
  return false;
}

template <size_t N>
Coordinate<N> Coordinate<N>::operator+(Coordinate<N> const &c) const {
  std::array<int, N> resultingArray;
  for (size_t i = 0; i < N; i++) {
    resultingArray[i] = coordinates[i] + c.coordinates[i];
  }
  return Coordinate(resultingArray);
}

template <size_t N>
Coordinate<N> Coordinate<N>::operator-(Coordinate<N> const &c) const {
  std::array<int, N> resultingArray;
  for (size_t i = 0; i < N; i++) {
    resultingArray[i] = coordinates[i] - c.coordinates[i];
  }
  return Coordinate(resultingArray);
}

template <size_t N> int Coordinate<N>::getX(void) const {
  return coordinates[0];
}

template <size_t N> int Coordinate<N>::getY(void) const {
  return coordinates[1];
}

template <size_t N>
template <size_t M>
decltype(auto) Coordinate<N>::get(void) const {
  if (M > N - 1) {
    throw std::out_of_range("Error: maximum amount of coordinates is " + N);
  }
  return coordinates[M];
}

template <size_t N>
std::ostream &operator<<(std::ostream &os, Coordinate<N> const &c) {
  os << "(";
  for (size_t i = 0; i < N - 1; i++) {
    os << c[i] << ", ";
  }

  os << c[N - 1] << ")";

  return os;
}
