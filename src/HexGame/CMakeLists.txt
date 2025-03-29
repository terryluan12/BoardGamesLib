
add_library(Coordinate INTERFACE)
target_include_directories(Coordinate INTERFACE .)

add_library(AxialDirection AxialDirection.cpp)
target_link_libraries(AxialDirection PUBLIC Coordinate)

add_library(Element Element.cpp)

add_library(Edge Edge.cpp)
target_link_libraries(Edge PUBLIC AxialDirection)
target_link_libraries(Edge PRIVATE Element)

add_library(Vertex Vertex.cpp)
target_link_libraries(Vertex PUBLIC AxialDirection)
target_link_libraries(Vertex PRIVATE Element Edge)

add_library(Common INTERFACE)
target_include_directories(Common INTERFACE .)