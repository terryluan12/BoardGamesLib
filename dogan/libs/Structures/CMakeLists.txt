
add_library(DoganStructureType DoganStructureType.cpp DoganStructureType.h)

add_library(DoganBuilding DoganBuilding.cpp DoganBuilding.h)
target_link_libraries(DoganBuilding PRIVATE DoganVertex DoganExceptions)
target_include_directories(DoganBuilding PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(DoganStructure DoganStructure.cpp DoganStructure.h)
target_link_libraries(DoganStructure PUBLIC DoganStructureType)
