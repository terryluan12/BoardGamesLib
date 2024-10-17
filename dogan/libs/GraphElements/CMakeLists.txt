
add_library(DoganEdge DoganEdge.cpp DoganEdge.h)
target_link_libraries(DoganEdge PUBLIC Coordinate enums)
target_include_directories(DoganEdge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(DoganVertex DoganVertex.cpp DoganVertex.h)
target_link_libraries(DoganVertex PUBLIC Coordinate enums)
target_include_directories(DoganEdge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
