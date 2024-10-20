add_subdirectory(Configuration)
add_subdirectory(GraphElements)
add_subdirectory(Structures)

add_library(DoganBank DoganBank.cpp DoganBank.h)
target_link_libraries(DoganBank PUBLIC enums)
target_link_libraries(DoganBank PRIVATE DoganExceptions)

add_library(DoganBoard DoganBoard.cpp DoganBoard.h)
target_link_libraries(DoganBoard PUBLIC DoganBank DoganCell DoganConfig DoganPlayer DoganBuilding DoganStructure)
target_link_libraries(DoganBoard PRIVATE Common DoganElementHelpers DoganCell)

add_library(DoganCell DoganCell.cpp DoganCell.h)
target_link_libraries(DoganCell PUBLIC Coordinate enums)

add_library(DoganPlayer DoganPlayer.cpp DoganPlayer.h)
target_link_libraries(DoganPlayer PUBLIC DoganBank DoganBuilding DoganStructure)
target_link_libraries(DoganPlayer PRIVATE DoganExceptions)

add_library(enums enums.cpp)
target_link_libraries(enums PUBLIC AxialHexDirection Common)

