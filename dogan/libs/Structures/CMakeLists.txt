
add_library(Building Building.cpp Building.h)
target_link_libraries(Building PRIVATE Exceptions)
target_include_directories(Building PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Structure Structure.cpp Structure.h)
target_link_libraries(Structure PUBLIC enums)
