
add_library(Coordinate INTERFACE)
target_include_directories(Coordinate INTERFACE .)

add_library(AxialHexDirection AxialHexDirection.cpp)
target_link_libraries(AxialHexDirection PUBLIC Coordinate)

add_library(Common INTERFACE)
target_include_directories(Common INTERFACE .)

add_library(CellInterface INTERFACE)
target_include_directories(CellInterface INTERFACE .)