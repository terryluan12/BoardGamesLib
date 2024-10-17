
add_library(Coordinate INTERFACE)
target_include_directories(Coordinate INTERFACE .)

add_library(HexagonalDirection HexagonalDirection.cpp HexagonalDirection.h)
target_link_libraries(HexagonalDirection PUBLIC Coordinate)

add_library(Common INTERFACE)
target_include_directories(Common INTERFACE .)

add_library(BoardInterface INTERFACE)
target_link_libraries(BoardInterface INTERFACE Common)
target_include_directories(BoardInterface INTERFACE .)

add_library(CellInterface INTERFACE)
target_include_directories(CellInterface INTERFACE .)