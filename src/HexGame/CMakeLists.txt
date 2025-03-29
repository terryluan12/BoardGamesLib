
add_library(Coordinate INTERFACE)
target_include_directories(Coordinate INTERFACE .)

add_library(AxialDirection AxialDirection.cpp)
target_link_libraries(AxialDirection PUBLIC Coordinate)

add_library(Edge Edge.cpp)
target_link_libraries(Edge AxialDirection)

add_library(Vertex Vertex.cpp)
target_link_libraries(Vertex Edge AxialDirection)

add_library(Common INTERFACE)
target_include_directories(Common INTERFACE .)